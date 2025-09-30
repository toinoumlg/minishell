/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/30 12:41:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	access_file(t_file *file, t_minishell *minishell)
{
	if (file->type == here_doc_quote || file->type == here_doc_word)
		return (set_here_doc(file, minishell));
	if (check_for_directory(file))
		return (0);
	set_access(file, file->path);
	return (0);
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

int	access_redirects(t_minishell *minishell, t_cmd *new_cmd)
{
	t_file	*redirects;

	redirects = new_cmd->redirects;
	if (!redirects)
		return (0);
	while (redirects)
	{
		if (access_file(redirects, minishell))
			return (1);
		redirects = redirects->next;
	}
	new_cmd->error = get_error_file(new_cmd->redirects);
	return (0);
}
