/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 18:32:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
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
	else if (cmd->infile->type == here_doc)
		return ;
}

void	dup2_write_pipe(t_pipex *pipex)
{
	if (dup2(pipex->pipe_fds[pipex->i - 1][0], STDIN_FILENO) == -1)
		perror("dup2 error:");
	close(pipex->pipe_fds[pipex->i - 1][0]);
}

void	dup2_outfile(t_pipex *pipex)
{
	if (pipex->cmds->outfile->type == output)
	{
		pipex->cmds->outfile->fd = open(pipex->cmds->outfile->path,
				O_CREAT | O_WRONLY, 0644);
		if (pipex->cmds->outfile->fd > 0)
		{
			if (dup2(pipex->cmds->outfile->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(pipex->cmds->outfile->fd);
			set_access(pipex->cmds->outfile);
		}
	}
	else if (pipex->cmds->outfile->type == append_file)
	{
		pipex->cmds->outfile->fd = open(pipex->cmds->outfile->path,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (pipex->cmds->outfile->fd > 0)
		{
			if (dup2(pipex->cmds->outfile->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(pipex->cmds->outfile->fd);
			set_access(pipex->cmds->outfile);
		}
	}
}

void	dup2_read_pipe(t_pipex *pipex)
{
	if (dup2(pipex->pipe_fds[pipex->i][1], STDOUT_FILENO) == -1)
		perror("dup2 error:");
	close(pipex->pipe_fds[pipex->i][1]);
}

void	set_file_fds(t_pipex *pipex)
{
	if (pipex->cmds->infile && !pipex->cmds->infile->read)
		dup2_infile(pipex->cmds);
	else if (!pipex->cmds->infile && pipex->i > 0 && pipex->pipe_fds)
		dup2_write_pipe(pipex);
	if (pipex->cmds->outfile && (pipex->cmds->outfile->exist
			|| !pipex->cmds->outfile->write))
		dup2_outfile(pipex);
	else if (!pipex->cmds->outfile && pipex->i < pipex->size - 1
		&& pipex->pipe_fds)
		dup2_read_pipe(pipex);
}
