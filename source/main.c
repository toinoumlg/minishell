/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 15:10:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "exec.h"
#include "minishell.h"
#include "parser/parse_read_line.h"
#include "signals.h"
#include <readline/readline.h>
#include <sys/wait.h>

sig_atomic_t	g_sig;

static void	handle_child_exit_status(t_minishell *minishell, int status)
{
	int	sig;

	minishell->last_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else
			ft_putstr_fd("\n", 1);
		minishell->last_status = 130;
	}
}

void	wait_for_childrens(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	if (!minishell->i || !minishell->pids)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < minishell->size)
		waitpid(minishell->pids[i++], &status, 0);
	set_signals();
	if (g_heredoc_interrupted == 0)
		handle_child_exit_status(minishell, status);
	if (minishell->pids)
		free(minishell->pids);
	minishell->pids = NULL;
}

static void	handle_signal_status(t_minishell *minishell)
{
	if (g_heredoc_interrupted == 2)
	{
		minishell->last_status = 130;
		g_heredoc_interrupted = 0;
	}
	if (g_heredoc_interrupted == 1)
	{
		minishell->last_status = 130;
		g_heredoc_interrupted = 0;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	rl_catch_signals = 0;
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (1);
	set_envp(&minishell, envp);
	set_signals();
	while (argv && argc)
	{
		minishell.read_line = readline("minishell> ");
		handle_signal_status(&minishell);
		if (!minishell.read_line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		parse_read_line(&minishell);
		exec(&minishell);
		wait_for_childrens(&minishell);
		handle_signal_status(&minishell);
	}
}
