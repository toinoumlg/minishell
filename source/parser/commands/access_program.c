/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:47:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/30 13:15:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

static void	set_access(t_file *file)
{
	int	fd;

	if (!ft_strncmp(file->path, ".", 2) || !ft_strncmp(file->path, "..", 3))
	{
		file->exist = 1;
		return ;
	}
	fd = open(file->path, __O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		file->is_dir = 1;
	}
	file->exist = access(file->path, F_OK);
	file->read = access(file->path, R_OK);
	file->write = access(file->path, W_OK);
	file->exec = access(file->path, X_OK);
}

static void	parse_env(t_minishell *minishell, t_file *program)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!*program->path || !ft_strncmp(program->path, ".", 2)
		|| !ft_strncmp(program->path, "..", 3) || !minishell->paths)
		return (set_access(program));
	while (minishell->paths[i])
	{
		tmp = ft_strjoin(minishell->paths[i], program->path);
		if (!tmp)
			exit_perror(minishell, "malloc");
		if (!access(tmp, F_OK))
		{
			free(program->path);
			program->path = tmp;
			set_access(program);
			return ;
		}
		free(tmp);
		i++;
	}
	program->exec = -1;
	program->exist = -1;
}

void	access_program(t_minishell *minishell, t_file *program)
{
	if (!minishell->cmds->args)
		return ;
	if (!ft_strchr(program->path, '/'))
		return (parse_env(minishell, program));
	set_access(program);
}
