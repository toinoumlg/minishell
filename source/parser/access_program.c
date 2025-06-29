/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:47:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 12:53:03 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	set_access(t_file *file, char *path)
{
	file->exist = access(path, F_OK);
	file->read = access(path, R_OK);
	file->write = access(path, W_OK);
	file->exec = access(path, X_OK);
}

static char	*parse_env(char **env, t_file *program)
{
	char	*tmp;

	while (*env)
	{
		tmp = ft_strjoin(*env, program->path);
		if (!tmp)
			return (free(program->path), NULL);
		if (!access(tmp, F_OK))
		{
			set_access(program, tmp);
			return (free(program->path), tmp);
		}
		free(tmp);
		env++;
	}
	set_access(program, program->path);
	return (program->path);
}

char	*access_program(t_file *program, char **env)
{
	if (ft_strncmp("/", program->path, 1))
		return (parse_env(env, program));
	else
		return (set_access(program, program->path), program->path);
}
