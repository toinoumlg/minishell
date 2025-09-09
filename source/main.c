/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 15:00:10 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "exec.h"
#include "free.h"
#include "parse_read_line.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "signals.h"
#include <unistd.h>

void	set_last_status(int status, int *last_status)
{
	if (status >= 0)
		*last_status = WEXITSTATUS(status);
	else
	{
		if (status == -2)
			*last_status = 1;
		if (status == -1)
			*last_status = 0;
	}
}

void	wait_for_childrens(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	while (i < minishell->size)
	{
		if (minishell->pids[i] >= 0)
			waitpid(minishell->pids[i++], &status, 0);
		else
			status = minishell->pids[i++];
	}
	set_last_status(status, &minishell->last_status);
	free(minishell->pids);
	minishell->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	set_envp(&minishell, envp);
	while (argv && argc)
	{
		set_signals();
		minishell.read_line = readline("minishell> ");
		parse_read_line(&minishell);
		exec(&minishell);
		wait_for_childrens(&minishell);
	}
	return (0);
}
