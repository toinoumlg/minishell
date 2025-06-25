/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:03:01 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:13:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

void	*alloc_pipe_fds(t_cmd *cmds, int size)
{
	int	**pipe_fds;

	if (!cmds->next)
		return (NULL);
	pipe_fds = malloc(sizeof(int[2]) * (size - 1));
	memset(pipe_fds, 0, sizeof(int[2]) * (size - 1));
	return (pipe_fds);
}

void	*alloc_pids(int size)
{
	int	*pid;

	pid = malloc(sizeof(int) * size);
	memset(pid, 0, sizeof(int) * size);
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
