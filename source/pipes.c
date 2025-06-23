/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:04:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/23 18:59:34 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	close_all_pipes(int (*pipe_fds)[2], int size, int i)
{
	int	j;

	j = -1;
	if (!pipe_fds)
		return ;
	while (++j <= i && j < size - 1)
	{
		close(pipe_fds[j][0]);
		close(pipe_fds[j][1]);
	}
}

void	dup2_pipes(int (*pipe_fds)[2], int size, int i)
{
	if (i == 0)
	{
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			perror("dup2 error:");
	}
	else if (i == size - 1)
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2 error:");
	}
	else
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2 error:");
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			perror("dup2 error:");
	}
	close_all_pipes(pipe_fds, size, i);
}
