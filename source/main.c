/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 20:00:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "free.h"
#include "libft.h"
#include "parse_read_line.h"
#include "set_env.h"
#include "utils.h"
#include <readline/readline.h>
#include <sys/wait.h>

void	is_exit(t_minishell *minishell, char **env)
{
	if (minishell->cmds && minishell->cmds->args
		&& !ft_strncmp(minishell->cmds->args[0], "exit", 4))
	{
		printf("exit\n");
		free_cmds(minishell->cmds);
		free_array(env);
		if (minishell->pipe_fds)
			free(minishell->pipe_fds);
		if (minishell->pids)
			free(minishell->pids);
		exit(0);
	}
	else
		return ;
}

void	wait_for_childrens(int *pids, int size)
{
	int	i;
	int	status;

	i = 0;
	while (i < size)
		waitpid(pids[i++], &status, 0);
	free(pids);
}

int	main(int argc, char **argv, char **envp)
{
	char		*read_line;
	char		**env;
	t_minishell	minishell;

	memset(&minishell, 0, sizeof(t_minishell));
	env = set_env(envp);
	if (!env)
		return (1);
	while (argc && argv)
	{
		read_line = readline("minishell >> ");
		parse_read_line(read_line, &minishell, env);
		is_exit(&minishell, env);
		exec(&minishell, envp);
		wait_for_childrens(minishell.pids, minishell.size);
		memset(&minishell, 0, sizeof(t_minishell));
	}
	free_array(env);
	return (0);
}
