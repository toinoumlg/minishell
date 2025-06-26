/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 18:33:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "free_utils.h"
#include "libft.h"
#include "parse_read_line.h"
#include "set_env.h"
#include "utils.h"
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

	memset(&minishell, 0, sizeof(t_minishell));
	minishell.env = set_env(envp);
	if (!minishell.env)
		return (1);
	while (argc && argv)
	{
		read_line = readline("minishell$ ");
		parse_read_line(read_line, &minishell.pipex, minishell.env);
		exec(&minishell.pipex, envp, minishell.env);
		wait_for_childrens(minishell.pipex.pids, minishell.pipex.size);
	}
	free_array(minishell.env);
	return (0);
}
