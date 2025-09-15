/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 14:05:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "init_envp.h"
#include "libft.h"
#include "parse_read_line.h"
#include "signals.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	wait_for_childrens(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	if (!minishell->i)
		return ;
	while (i < minishell->size)
	{
		if (minishell->pids[i] >= 0)
			waitpid(minishell->pids[i++], &status, 0);
		else
			status = minishell->pids[i++];
	}
	minishell->last_status = WEXITSTATUS(status);
	if (minishell->pids)
		free(minishell->pids);
	minishell->pids = NULL;
}


int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char		*line;

	// if (!isatty(0) || !isatty(1) || !isatty(2))
	// 	return (1);
	init_envp(&minishell, envp);
	set_signals();
	while (argv && argc)
	{
		if (isatty(fileno(stdin)))
			minishell.read_line = readline("minishell> ");
		else
		{
			line = get_next_line(fileno(stdin));
			minishell.read_line = ft_strtrim(line, "\n");
			free(line);
		}
		// minishell.read_line = readline("minishell> ");
		parse_read_line(&minishell);
		exec(&minishell);
		wait_for_childrens(&minishell);
	}
	return (0);
}
