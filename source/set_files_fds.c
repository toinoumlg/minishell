/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 20:11:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	dup2_infile(t_cmd *cmd)
{
	if (cmd->infile->type == input)
	{
		cmd->infile->fd = open(cmd->infile->path, O_RDONLY);
		if (cmd->infile->fd > 0)
		{
			if (dup2(cmd->infile->fd, STDIN_FILENO))
				perror("dup2 error:");
			close(cmd->infile->fd);
		}
	}
	else
		return ;
}

void	dup2_write_pipe(t_minishell *minishell)
{
	if (dup2(minishell->pipe_fds[minishell->i - 1][0], STDIN_FILENO) == -1)
		perror("dup2 error:");
	close(minishell->pipe_fds[minishell->i - 1][0]);
}

void	dup2_outfile(t_minishell *minishell)
{
	if (minishell->cmds->outfile->type == output)
	{
		minishell->cmds->outfile->fd = open(minishell->cmds->outfile->path,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (minishell->cmds->outfile->fd > 0)
		{
			if (dup2(minishell->cmds->outfile->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(minishell->cmds->outfile->fd);
		}
	}
	else
	{
		minishell->cmds->outfile->fd = open(minishell->cmds->outfile->path,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (minishell->cmds->outfile->fd > 0)
		{
			if (dup2(minishell->cmds->outfile->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(minishell->cmds->outfile->fd);
		}
	}
}

void	dup2_read_pipe(t_minishell *minishell)
{
	if (dup2(minishell->pipe_fds[minishell->i][1], STDOUT_FILENO) == -1)
		perror("dup2 error:");
	close(minishell->pipe_fds[minishell->i][1]);
}

void	set_file_fds(t_minishell *minishell)
{
	if (minishell->cmds->infile && !minishell->cmds->infile->read)
		dup2_infile(minishell->cmds);
	else if (!minishell->cmds->infile && minishell->i > 0
		&& minishell->pipe_fds)
		dup2_write_pipe(minishell);
	if (minishell->cmds->outfile && (minishell->cmds->outfile->exist
			|| !minishell->cmds->outfile->write))
		dup2_outfile(minishell);
	else if (!minishell->cmds->outfile && minishell->i < minishell->size - 1
		&& minishell->pipe_fds)
		dup2_read_pipe(minishell);
}
