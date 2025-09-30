/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/30 14:09:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parser/token.h"
#include "redirects.h"
#include "signals.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	exit_on_eof(char *lim)
{
	write(2, "minishell: warning: here-document delimited by end-of-file (wanted `", 68);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 3);
}

/*	Expands variable on read_line string.
	Works like token expansion but modifies the read_line string directly	*/
static void	write_here_doc(int fd, char *lim)
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
		read_line = readline("> ");
		if (g_sig)
			return ;
		if (!read_line)
			return (exit_on_eof(lim));
		if (!ft_strncmp(read_line, lim, ft_strlen(lim) + 1))
			return (free(read_line));
		write(fd, read_line, ft_strlen(read_line));
		write(fd, "\n", 1);
		free(read_line);
	}
	_exit(0);
}

int	here_doc_received_signal(int fd, t_minishell *minishell)
{
	minishell->last_status = 130;
	free_cmds(minishell->cmds);
	free_tokens(minishell->tokens);
	ft_close(&fd);
	minishell->cmds = NULL;
	minishell->tokens = NULL;
	g_sig = 0;
	return (1);
}

// fd[1] is for writing file
// fd[0] is for reading file
int	set_here_doc(t_file *here_doc_file, t_minishell *minishell)
{
	int					fd_wr;
	int					fd_rd;
	pid_t				pid;
	int					status;
	struct sigaction	sa_ign;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	g_sig = 0;
	dup_std_copy(minishell);
	signal(SIGINT, heredoc_sigint_handler);
	fd[1] = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd[1] == -1)
		exit_perror(minishell, "open");
	fd[0] = open("/tmp/here_doc", O_RDONLY);
	if (fd[0] == -1)
		exit_perror(minishell, "open");
	unlink("/tmp/here_doc");
	write_here_doc(fd[1], here_doc_file->path);
	ft_close(&fd[1]);
	here_doc_file->fd = fd[0];
	set_signals();
	dup2_std_copy(minishell);
	if (g_sig)
		return (here_doc_received_signal(fd[0], minishell));
	return (0);
}
