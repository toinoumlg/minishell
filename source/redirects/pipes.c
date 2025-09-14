/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:04:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 12:59:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	close_pipes(int (*pipe_fds)[2], int size, int i)
{
	if (!pipe_fds)
		return ;
	if (i == 0)
		close(pipe_fds[i][1]);
	else if (i == size - 1)
		close(pipe_fds[i - 1][0]);
	else
	{
		close(pipe_fds[i][1]);
		close(pipe_fds[i - 1][0]);
	}
}

void	dup2_pipes(int (*pipe_fds)[2], int size, int i, t_minishell *minishell)
{
	if (i == 0)
	{
		close(pipe_fds[i][0]);
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2");
		close(pipe_fds[i][1]);
	}
	else if (i == size - 1)
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			exit_perror(minishell, "dup2");
		close(pipe_fds[i - 1][0]);
	}
	else
	{
		close(pipe_fds[i][0]);
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			exit_perror(minishell, "dup2");
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2");
		close(pipe_fds[i][1]);
		close(pipe_fds[i - 1][0]);
	}
}

static int	need_to_pipe(t_minishell *minishell)
{
	return (minishell->size > 1 && minishell->i < minishell->size - 1);
}

// creates pipe if needed
void	do_pipe(t_minishell *minishell)
{
	if (need_to_pipe(minishell))
		if (pipe(minishell->pipe_fds[minishell->i]) == -1)
			exit_perror(minishell, "pipe");
}
