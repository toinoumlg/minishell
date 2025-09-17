/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/18 02:32:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "here_doc_utils.h"
#include "libft.h"
#include "signals.h"
#include "token_list.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*  Warning affiché quand EOF (Ctrl-D) arrive avant le délimiteur             */
/* -------------------------------------------------------------------------- */
static void	exit_on_eof(char *lim)
{
	write(2, "minishell: warning: here-document delimited by end-of-file (wanted `", 68);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 3);
}

/* -------------------------------------------------------------------------- */
/*  ENFANT : lit le heredoc et écrit dans fd_write                             */
/*  - Ctrl-C  (SIGINT)  : comportement par défaut -> tue l'enfant              */
/*  - Ctrl-\\ (SIGQUIT) : IGNORÉ -> ne doit PAS quitter le heredoc             */
/* -------------------------------------------------------------------------- */
static void	collect_heredoc_child(int fd_write, char *lim)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				*line;

	/* SIGINT: défaut */
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_int, NULL);

	/* SIGQUIT: ignoré */
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			/* Ctrl-D : EOF -> warning puis fin normale */
			exit_on_eof(lim);
			break ;
		}
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	_exit(0);
}

/* -------------------------------------------------------------------------- */
/*  API                                                                        */
/* -------------------------------------------------------------------------- */
/* fd[1] is for writing file                                                   */
/* fd[0] is for reading file                                                   */
void	set_here_doc(t_file *here_doc_file)
{
	int					fd_wr;
	int					fd_rd;
	pid_t				pid;
	int					status;
	struct sigaction	sa_ign;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	/* Écrit le contenu saisi dans un fichier temporaire simple */
	fd_wr = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd_wr < 0)
	{
		here_doc_file->fd = -1;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd_wr);
		here_doc_file->fd = -1;
		return ;
	}
	if (pid == 0)
	{
		/* ENFANT heredoc : collecte (Ctrl-\ ignoré, Ctrl-C tue l’enfant) */
		collect_heredoc_child(fd_wr, here_doc_file->path);
	}
	/* PARENT */
	close(fd_wr);

	/* Ignorer SIGINT/SIGQUIT pendant l'attente pour éviter le doublon d'affichage */
	sigemptyset(&sa_ign.sa_mask);
	sa_ign.sa_flags = 0;
	sa_ign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_ign, &old_int);
	sigaction(SIGQUIT, &sa_ign, &old_quit);

	if (waitpid(pid, &status, 0) < 0)
		status = 1;

	/* Restaurer les handlers du parent tels qu'ils étaient avant l'attente */
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);

	/* Affichage propre si interrompu: évite "minishell> > " résiduel */
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);

	/* Si interrompu par Ctrl-C : neutraliser le heredoc côté exécution */
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		here_doc_file->fd = open("/dev/null", O_RDONLY);
		unlink("/tmp/here_doc");
		return ;
	}

	/* Fin normale (délimiteur) ou EOF (warning déjà imprimé côté enfant) */
	fd_rd = open("/tmp/here_doc", O_RDONLY);
	here_doc_file->fd = fd_rd;
	unlink("/tmp/here_doc");
}
