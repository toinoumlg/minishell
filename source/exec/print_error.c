/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:12:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 11:24:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_error_no_file_or_dir(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	print_error_no_permission(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	print_error_is_a_directory(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void	print_error_file(t_file *error)
{
	if (!error)
		return ;
	if (error->type == input)
	{
		if (error->exist)
			print_error_no_file_or_dir(error->path);
		if (!error->exist && error->read)
			print_error_no_permission(error->path);
		if (error->is_dir)
			print_error_is_a_directory(error->path);
	}
	if (error->type == output || error->type == append_file)
	{
		if (error->write)
			print_error_no_permission(error->path);
		if (error->is_dir)
			print_error_is_a_directory(error->path);
	}
}

int	print_command_error(t_file *program, t_file *error)
{
	if (error)
		return (1);
	if (program->is_dir)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(program->path, 2),
			ft_putstr_fd(": Is a directory\n", 2), 126);
	if (program->exist)
	{
		if (ft_strchr(program->path, '/'))
			return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(program->path,
					2), ft_putstr_fd(": No such file or directory\n", 2), 127);
		else
			return (ft_putstr_fd(program->path, 2),
				ft_putstr_fd(": command not found\n", 2), 127);
	}
	if (program->exec)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(program->path, 2),
			ft_putstr_fd(": Permission denied\n", 2), 126);
	return (0);
}
