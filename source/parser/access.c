/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/24 16:49:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access_program.h"
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
	if (file->type == here_doc)
		return ;
	if (check_for_directory(file))
		return ;
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

void	try_access(t_cmd *cmds, char **env)
{
	t_file	*redirects;

	while (cmds)
	{
		cmds->program->path = access_program(cmds->program, env);
		redirects = cmds->redirects;
		while (redirects)
		{
			access_file(redirects);
			// besoin de faire la prise de here doc ici le here_doc aura un fd 
			// qui correspond au fd pour read le pipe qui dans lequel on ecrit.
			if(redirects->type == here_doc)
				get_here_doc();
			redirects = redirects->next;
		}
		cmds->error = get_error_file(cmds->redirects);
		cmds = cmds->next;
	}
}
