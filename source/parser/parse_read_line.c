/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 10:16:03 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_read_line.h"

void	pre_parsing(t_minishell *minishell)
{
	minishell->i = 0;
	set_env_array(minishell);
	set_envp_array(minishell);
}

void	post_parsing(t_minishell *minishell)
{
	if (!minishell->cmds)
		return ;
	try_access(minishell->cmds, minishell->env);
	minishell->size = set_size(minishell->cmds);
	minishell->pipe_fds = alloc_pipe_fds(minishell);
	minishell->pids = alloc_pids(minishell);
}

void	parse_read_line(t_minishell *minishell)
{
	if (!minishell->read_line)
	{
		free_minishell(minishell);
		// write(2, "exit\n", 5);
		exit(0);
	}
	add_history(minishell->read_line);
	pre_parsing(minishell);
	generate_tokens(minishell);
	set_commands(minishell);
	post_parsing(minishell);
}
