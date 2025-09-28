/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 14:12:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parse_read_line.h"
#include "signals.h"

void	pre_parsing(t_minishell *minishell)
{
	minishell->i = 0;
	minishell->size = 0;
	set_paths(minishell);
	set_envp_array(minishell);
}

void	post_parsing(t_minishell *minishell)
{
	if (!minishell->cmds)
		return ;
	try_access(minishell);
	minishell->size = set_size(minishell->cmds);
	minishell->pipe_fds = alloc_pipe_fds(minishell);
	minishell->pids = alloc_pids(minishell);
}

void	handle_signal_status(t_minishell *minishell)
{
	if (g_sig)
	{
		minishell->last_status = 130;
		g_sig = 0;
	}
}

void	parse_read_line(t_minishell *minishell)
{
	handle_signal_status(minishell);
	if (!minishell->read_line)
	{
		write(1, "exit\n", 5);
		clear_history();
		exit(free_minishell(minishell));
	}
	add_history(minishell->read_line);
	pre_parsing(minishell);
	generate_tokens(minishell);
	set_commands(minishell);
	post_parsing(minishell);
}
