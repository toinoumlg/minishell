/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 18:30:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "free_utils.h"
#include "libft.h"
#include "parse_read_line.h"
#include "set_envs.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include <sys/wait.h>

void	wait_for_childrens(int *pids, int size)
{
	int	i;
	int	status;

	i = 0;
	while (i < size)
	{
		if (pids[i] > 0)
			waitpid(pids[i++], &status, 0);
		else
			i++;
	}
	free(pids);
}

int	main(int argc, char **argv, char **envp)
{
	char		*read_line;
	t_minishell	minishell;

	envp = NULL;
	memset(&minishell, 0, sizeof(t_minishell));
	set_envs(&minishell, envp);
	if (!minishell.env)
		return (1);
	while (argv && argc)
	{
		read_line = readline("minishell> ");
		parse_read_line(read_line, &minishell.pipex, &minishell);
		exec(&minishell.pipex);
		wait_for_childrens(minishell.pipex.pids, minishell.pipex.size);
	}
	free_array(minishell.env);
	return (0);
}
