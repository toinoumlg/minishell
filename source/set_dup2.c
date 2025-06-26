/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 16:30:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "here_doc.h"
#include "minishell.h"
#include "pipes.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	dup2_infile(t_file *infile)
{
	if (!infile->read)
	{
		infile->fd = open(infile->path, O_RDONLY);
		if (infile->fd > 0)
		{
			if (dup2(infile->fd, STDIN_FILENO))
				perror("dup2 error:");
			close(infile->fd);
		}
	}
}

void	dup2_outfile(t_file *outfile)
{
	if (outfile->exist || !outfile->write)
	{
		outfile->fd = open(outfile->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile->fd > 0)
		{
			if (dup2(outfile->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(outfile->fd);
			set_access(outfile);
		}
	}
}

static void	dup2_append_file(t_file *append_file)
{
	if (append_file->exist || !append_file->write)
	{
		append_file->fd = open(append_file->path, O_CREAT | O_WRONLY | O_APPEND,
				0644);
		if (append_file->fd > 0)
		{
			if (dup2(append_file->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(append_file->fd);
			set_access(append_file);
		}
	}
}

void	set_dup2(t_pipex *pipex)
{
	if (pipex->cmds->here_doc)
		set_here_doc(pipex);
	if (pipex->pipe_fds)
		dup2_pipes(pipex->pipe_fds, pipex->size, pipex->i);
	if (pipex->cmds->infile)
		dup2_infile(pipex->cmds->infile);
	if (pipex->cmds->append_file)
		dup2_append_file(pipex->cmds->append_file);
	if (pipex->cmds->outfile)
		dup2_outfile(pipex->cmds->outfile);
}
