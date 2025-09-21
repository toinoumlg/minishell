/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 07:50:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access_program.h"
#include "builtsin.h"
#include "libft.h"
#include "redirects.h"
#include <fcntl.h>
#include <stdio.h>

static void	set_access(t_file *file, char *path)
{
	char	*folder_path;
	int		folder_fd;

	folder_path = ft_strrchr(path, '/');
	if (folder_path)
	{
		*folder_path = 0;
		folder_fd = open(file->path, __O_DIRECTORY);
		*folder_path = '/';
		if (folder_fd < 0)
		{
			file->is_dir = 2;
			return ;
		}
		close(folder_fd);
	}
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

static void	access_file(t_file *file, t_minishell *minishell)
{
	if (check_for_directory(file))
		return ;
	if (file->type == here_doc_quote || file->type == here_doc_word)
		set_here_doc(file, minishell);
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
			access_file(redirects, minishell);
			redirects = redirects->next;
		}
		cmds->error = get_error_file(cmds->redirects);
		cmds = cmds->next;
	}
}
