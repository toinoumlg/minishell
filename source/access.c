/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 18:57:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

void	set_all_access_to_n(t_file *program, int n)
{
	program->exist = n;
	program->exec = n;
	program->read = n;
	program->write = n;
}

char	*parse_env(char **env, t_file *program)
{
	char	*tmp;

	set_all_access_to_n(program, -1);
	while (*env)
	{
		tmp = ft_strjoin(*env, program->path);
		if (!tmp)
			return (free(program->path), NULL);
		if (!access(tmp, F_OK))
		{
			program->exist = access(tmp, F_OK);
			program->exec = access(tmp, X_OK);
			program->read = access(tmp, R_OK);
			program->write = access(tmp, W_OK);
			return (free(program->path), tmp);
		}
		free(tmp);
		env++;
	}
	return (program->path);
}

int	check_for_directory(t_file *file)
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

void	set_access(t_file *file)
{
	file->exist = access(file->path, F_OK);
	file->read = access(file->path, R_OK);
	file->write = access(file->path, W_OK);
	file->exec = access(file->path, X_OK);
}

void	access_file(t_file *file)
{
	if (!file)
		return ;
	if (check_for_directory(file))
		return ;
	set_access(file);
}

char	*access_program(t_file *program, char **env)
{
	if (ft_strncmp("/", program->path, 1))
		return (parse_env(env, program));
	else
		return (set_access(program), program->path);
}

void	try_access(t_cmd *cmds, char **env)
{
	while (cmds)
	{
		cmds->program->path = access_program(cmds->program, env);
		access_file(cmds->infile);
		access_file(cmds->outfile);
		cmds = cmds->next;
	}
}
