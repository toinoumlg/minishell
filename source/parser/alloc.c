/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:03:01 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 10:59:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <stdlib.h>
#include <string.h>

void	alloc_pipe_fds(t_minishell *minishell)
{
	if (!minishell->cmds->next)
	{
		minishell->pipe_fds = NULL;
		return ;
	}
	minishell->pipe_fds = malloc(sizeof(int[2]) * (minishell->size - 1));
	if (!minishell->pipe_fds)
		exit_perror(minishell, "malloc :");
	memset(minishell->pipe_fds, 0, sizeof(int[2]) * (minishell->size - 1));
}

void	alloc_pids(t_minishell *minishell)
{
	minishell->pids = malloc(sizeof(int) * minishell->size);
	if (!minishell->pids)
		exit_perror(minishell, "malloc :");
	memset(minishell->pids, 0, sizeof(int) * minishell->size);
}

void	set_size(t_minishell *minishell)
{
	t_cmd	*cmds;

	cmds = minishell->cmds;
	minishell->size = 0;
	while (cmds)
	{
		minishell->size++;
		cmds = cmds->next;
	}
}
