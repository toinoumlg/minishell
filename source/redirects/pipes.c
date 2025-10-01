/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:04:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/10/01 18:23:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirects.h"
#include "free.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	close_here_doc(t_file *redirects)
{
	while (redirects)
	{
		if (redirects->type == here_doc_quote
			|| redirects->type == here_doc_word)
			fd_close(&redirects->fd);
		redirects = redirects->next;
	}
}

/*	Same logic as dup2_pipes but we only close pipes for the parent	*/
void	close_pipes(int (*pipe_fds)[2], int size, int i)
{
	if (!pipe_fds)
		return ;
	if (i == 0)
		fd_close(&pipe_fds[i][1]);
	else if (i == size - 1)
		fd_close(&pipe_fds[i - 1][0]);
	else
	{
		fd_close(&pipe_fds[i][1]);
		fd_close(&pipe_fds[i - 1][0]);
	}
}

/*	Redirects stdin/out to appropriate pipe fd based on command position
	First command : stdout to pipe
	Middle command: stdin from previous pipe and stdout to current pipe
	Last command: stdin from prevous pipe	*/
void	dup2_pipes(int (*pipe_fds)[2], int size, int i, t_minishell *minishell)
{
	if (i == 0)
	{
		fd_close(&pipe_fds[i][0]);
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2");
		fd_close(&pipe_fds[i][1]);
	}
	else if (i == size - 1)
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			exit_perror(minishell, "dup2");
		fd_close(&pipe_fds[i - 1][0]);
	}
	else
	{
		fd_close(&pipe_fds[i][0]);
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			exit_perror(minishell, "dup2");
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2");
		fd_close(&pipe_fds[i][1]);
		fd_close(&pipe_fds[i - 1][0]);
	}
}

/*	Creates a pipe if there are multiple commands
	Only creates pipes between commands, so stops at size - 1	*/
void	do_pipe(t_minishell *minishell)
{
	if (minishell->size > 1 && minishell->i < minishell->size - 1)
		if (pipe(minishell->pipe_fds[minishell->i]) == -1)
			exit_perror(minishell, "pipe");
}
