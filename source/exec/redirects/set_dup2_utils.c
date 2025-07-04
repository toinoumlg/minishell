/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:16:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	dup2_infile(t_file *infile)
{
	if (!infile->read)
	{
		infile->fd = open(infile->path, O_RDONLY);
		if (infile->fd > 0)
		{
			if (dup2(infile->fd, STDIN_FILENO))
				return (1);
			close(infile->fd);
			return (0);
		}
	}
	return (0);
}

int	dup2_outfile(t_file *outfile)
{
	if (outfile->exist || !outfile->write)
	{
		outfile->fd = open(outfile->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile->fd > 0)
		{
			if (dup2(outfile->fd, STDOUT_FILENO) == -1)
				return (1);
			close(outfile->fd);
			return (0);
		}
	}
	return (0);
}

int	dup2_append_file(t_file *append_file)
{
	if (append_file->exist || !append_file->write)
	{
		append_file->fd = open(append_file->path, O_CREAT | O_WRONLY | O_APPEND,
				0644);
		if (append_file->fd > 0)
		{
			if (dup2(append_file->fd, STDOUT_FILENO) == -1)
				return (1);
			close(append_file->fd);
			return (0);
		}
	}
	return (0);
}

int	contains_type(t_file *redirects, t_enum_token type)
{
	if (!redirects)
		return (0);
	while (redirects)
	{
		if (redirects->type == type)
			return (1);
		redirects = redirects->next;
	}
	return (0);
}

void	exit_set_files_in_child(t_minishell *minishell)
{
	free_on_exit_error(minishell);
	perror("set_file");
	exit(1);
}
