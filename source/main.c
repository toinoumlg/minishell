/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 14:34:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "exec.h"
#include "parser/parse_read_line.h"
#include "signals.h"
#include <readline/readline.h>
#include <sys/wait.h>

void	wait_for_childrens(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	if (!minishell->i)
		return ;
	while (i < minishell->size)
		waitpid(minishell->pids[i++], &status, 0);
	minishell->last_status = WEXITSTATUS(status);
	if (minishell->pids)
		free(minishell->pids);
	minishell->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (1);
	set_envp(&minishell, envp);
	set_signals();
	while (argv && argc)
	{
		minishell.read_line = readline("minishell> ");
		parse_read_line(&minishell);
		exec(&minishell);
		wait_for_childrens(&minishell);
	}
}
