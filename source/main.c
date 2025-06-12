/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/12 21:19:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parse_read_line.h"
#include "set_env.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>


void set_fds(t_cmd *cmd, int ** pi)
{
	
}

void forked_cmds(cmd)
{
	
	set_fds();
}

void	exec_one(t_cmd *cmd, int (*pipe_fds)[2], int *pids, int i)
{
	if (cmd->next)
		if (pipe(pipe_fds[i]) == -1)
			exit(printf("pipe creation error\n"));
	pids[i] = fork();
	if (pids[i] == -1)
		exit(printf("fork error\n"));
	if(pids[i] == 0)
		forked_cmd();
	else
	{
		
	}
}

void	exec(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->cmds)
	{
		exec_one(minishell->cmds, minishell->pipe_fds, i++);
		print_commands(minishell->cmds);
		free_and_set_to_next_commands(&minishell->cmds);
	}
}

int	is_exit(t_cmd *cmds)
{
	if (cmds && cmds->args && !ft_strncmp(cmds->args[0], "exit", 4))
		return (printf("exit\n"), free_cmds(cmds), 1);
	else
		return (0);
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
		if (is_exit(minishell.cmds))
			return (0);
		exec(&minishell);
		memset(&minishell, 0, sizeof(t_minishell));
	}
	return (0);
}
