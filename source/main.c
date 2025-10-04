/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/10/04 13:58:02 by amalangu         ###   ########.fr       */
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

static void	handle_exit_status(t_minishell *minishell, int status, int *exited)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT && !*exited)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT && !*exited)
			ft_putstr_fd("\n", 1);
		minishell->last_status = 128 + sig;
		(*exited)++;
	}
	else
		minishell->last_status = WEXITSTATUS(status);
}

void	wait_for_childrens(t_minishell *minishell)
{
	int	i;
	int	status;
	int	exited;

	exited = 0;
	i = 0;
	if (!minishell->i || !minishell->pids)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < minishell->size)
	{
		waitpid(minishell->pids[i++], &status, 0);
		handle_exit_status(minishell, status, &exited);
	}
	signal(SIGINT, sigint_handler_main);
	if (minishell->pids)
		free(minishell->pids);
	minishell->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
		|| !isatty(STDOUT_FILENO))
		return (1);
	set_envp(&minishell, envp);
	set_signals();
	while (argv && argc)
	{
		rl_on_new_line();
		minishell.read_line = readline("minishell> ");
		parse_read_line(&minishell);
		exec(&minishell);
		wait_for_childrens(&minishell);
	}
}
