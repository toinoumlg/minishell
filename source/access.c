/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:06 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 18:52:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

char	*parse_env(char **env, char *path)
{
	char	*tmp;

	while (*env)
	{
		tmp = ft_strjoin(*env, path);
		if (!tmp)
			return (free(path), NULL);
		if (!access(tmp, X_OK))
			return (free(path), tmp);
		free(tmp);
		env++;
	}
	return (path);
}

char	*access_program(char *program_path, char **env)
{
	if (ft_strncmp("/", program_path, 1))
		return (parse_env(env, program_path));
	else
		return (program_path);
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

void	try_access(t_cmd *cmds, char **env)
{
	while (cmds)
	{
		cmds->program_path = access_program(cmds->program_path, env);
		if (!cmds->program_path)
			return ;
		access_file(cmds->infile);
		access_file(cmds->outfile);
		cmds = cmds->next;
	}
}
