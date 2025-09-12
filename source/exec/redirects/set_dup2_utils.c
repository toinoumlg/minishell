/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 20:15:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	dup2_infile(t_file *infile, t_minishell *minishell)
{
	infile->fd = open(infile->path, O_RDONLY);
	if (infile->fd > 0)
	{
		if (dup2(infile->fd, STDIN_FILENO))
			exit_perror(minishell, "dup2 ");
		close(infile->fd);
	}
	else
		exit_perror(minishell, "open ");
}

void	dup2_outfile(t_file *outfile, t_minishell *minishell)
{
	outfile->fd = open(outfile->path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (outfile->fd > 0)
	{
		if (dup2(outfile->fd, STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2 ");
		close(outfile->fd);
	}
	else
		exit_perror(minishell, "open ");
}

void	dup2_append_file(t_file *append_file, t_minishell *minishell)
{
	append_file->fd = open(append_file->path, O_CREAT | O_WRONLY | O_APPEND,
			0600);
	if (append_file->fd > 0)
	{
		if (dup2(append_file->fd, STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2 ");
		close(append_file->fd);
	}
	else
		exit_perror(minishell, "open ");
}

void	dup2_here_doc(t_file *here_doc_file, t_minishell *minishell)
{
	if (dup2(here_doc_file->fd, STDIN_FILENO))
		exit_perror(minishell, "dup2 ");
	close(here_doc_file->fd);
}
