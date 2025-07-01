/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 18:28:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_utils.h"
#include "minishell.h"
#include <readline/history.h>
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

void	free_envp(t_envp *envp)
{
	t_envp	*next;

	while (envp)
	{
		next = envp->next;
		if (envp->line)
			free(envp->line);
		if (envp->name)
			free(envp->name);
		if (envp->value)
			free(envp->value);
		free(envp);
		envp = next;
	}
}
void	free_child(t_pipex *pipex)
{
	free_cmds(pipex->cmds);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->pipe_fds)
		free(pipex->pipe_fds);
	free_array(pipex->env);
	free_array(pipex->envp_array);
	free_envp(*pipex->envp);
	clear_history();
}
