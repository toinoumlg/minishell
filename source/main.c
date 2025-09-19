/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 19:25:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env/init_envp.h"
#include "free.h"
#include "parser/parse_read_line.h"
#include "signals.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>

/* -------------------------------------------------------------------------- */
/* Parent: ignorer pendant exec, puis restaurer les handlers de prompt        */
/* (locales à ce fichier)                                                     */
/* -------------------------------------------------------------------------- */
static void	parent_ignore_signals_during_exec(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	parent_restore_prompt_signals(void)
{
	set_signals();
}

/* -------------------------------------------------------------------------- */
/* Attente enfants + statut                                                   */
/* -------------------------------------------------------------------------- */
static void	update_status_and_display(t_minishell *ms, int status)
{
	if (WIFSIGNALED(status) != 0)
	{
		int	sig;

		sig = WTERMSIG(status);
		ms->last_status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
	else if (WIFEXITED(status) != 0)
		ms->last_status = WEXITSTATUS(status);
}

static void	wait_for_childrens(t_minishell *ms)
{
	int		i;
	int		status;
	pid_t	w;

	i = 0;
	if (ms->pids == NULL)
		return ;
	while (i < ms->size)
	{
		if (ms->pids[i] > 0)
		{
			w = waitpid((pid_t)ms->pids[i], &status, 0);
			if (w > 0)
				update_status_and_display(ms, status);
		}
		i = i + 1;
	}
	free(ms->pids);
	ms->pids = NULL;
}

/* -------------------------------------------------------------------------- */
/* Readline wrapper : force TTY sain avant/après readline                     */
/* -------------------------------------------------------------------------- */
static void	force_tty_sane_inline(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == 0)
	{
		t.c_lflag |= ECHO;
		t.c_lflag |= ICANON;
		t.c_lflag |= ISIG;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
}

char	*ms_readline(const char *prompt)
{
	char	*line;

	/* au cas où le heredoc précédent a laissé le TTY en vrac */
	tty_restore_initial_state();
	force_tty_sane_inline();
	set_signals();

	line = readline(prompt);

	/* après readline, on re-sanitise pour éviter l’echo coupé */
	tty_restore_initial_state();
	force_tty_sane_inline();
	return (line);
}

/* -------------------------------------------------------------------------- */
/* main                                                                       */
/* -------------------------------------------------------------------------- */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	memset(&minishell, 0, sizeof(minishell));

	init_envp(&minishell, envp);
	signals_bind_minishell(&minishell);

	tty_save_initial_state();
	set_signals();

	while (1)
	{
		minishell.read_line = ms_readline("minishell> ");
		parse_read_line(&minishell);

		parent_ignore_signals_during_exec();
		exec(&minishell);
		wait_for_childrens(&minishell);
		parent_restore_prompt_signals();
	}
	return (0);
}
