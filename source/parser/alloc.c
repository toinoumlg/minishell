/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:03:01 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/04 15:09:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <stdlib.h>
#include <string.h>

void	*alloc_pipe_fds(t_minishell *minishell)
{
	int	**pipe_fds;

	if (!minishell->cmds->next)
		return (NULL);
	pipe_fds = malloc(sizeof(int [2]) * (minishell->size - 1));
	if (!pipe_fds)
		exit(free_on_exit_error(minishell));
	memset(pipe_fds, 0, sizeof(int [2]) * (minishell->size - 1));
	return (pipe_fds);
}

void	*alloc_pids(t_minishell *minishell)
{
	int	*pid;

	pid = malloc(sizeof(int) * minishell->size);
	if (!pid)
		exit(free_on_exit_error(minishell));
	memset(pid, 0, sizeof(int) * minishell->size);
	return (pid);
}

int	set_size(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}
