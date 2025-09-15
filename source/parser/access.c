/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 16:56:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access_program.h"
#include "builtsin.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

static void	set_access(t_file *file, char *path)
{
	file->exist = access(path, F_OK);
	file->read = access(path, R_OK);
	file->write = access(path, W_OK);
	file->exec = access(path, X_OK);
}

static int	check_for_directory(t_file *file)
{
	int	fd;

	fd = open(file->path, __O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		file->is_dir = 1;
		return (1);
	}
	else
		return (0);
}

static void	access_file(t_file *file)
{
	if (check_for_directory(file))
		return ;
	if (file->type == here_doc)
		set_here_doc(file);
	set_access(file, file->path);
}

static t_file	*get_error_file(t_file *redirects)
{
	while (redirects)
	{
		if (redirects->is_dir)
			return (redirects);
		if (redirects->type == input && !(!redirects->read))
			return (redirects);
		if ((redirects->type == output || redirects->type == append_file)
			&& !(redirects->exist || !redirects->write))
			return (redirects);
		redirects = redirects->next;
	}
	return (NULL);
}

void	try_access(t_minishell *minishell)
{
	t_file	*redirects;
	t_cmd	*cmds;

	cmds = minishell->cmds;
	while (cmds)
	{
		if (cmds->program && !is_a_builtin(cmds->program->path))
			access_program(minishell, cmds->program);
		redirects = cmds->redirects;
		while (redirects)
		{
			access_file(redirects);
			redirects = redirects->next;
		}
		cmds->error = get_error_file(cmds->redirects);
		cmds = cmds->next;
	}
}
