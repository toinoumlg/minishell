/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 19:21:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_utils.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_cmd(cmds);
		cmds = next;
	}
}

void	free_and_set_to_next_commands(t_cmd **cmds)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *cmds;
	next = tmp->next;
	free_cmd(tmp);
	*cmds = next;
}

void	free_child(t_pipex *pipex)
{
	free_cmds(pipex->cmds);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->pipe_fds)
		free(pipex->pipe_fds);
	free_array(pipex->env);
}
