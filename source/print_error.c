/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:12:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 12:04:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_error_no_file_or_dir(char *path)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	print_error_no_permission(char *path)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	print_error_is_a_directory(char *path)
{
	ft_putstr_fd("minishell: is a directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	print_error_file(t_file *input, t_file *output)
{
	if (input)
	{
		if (input->exist)
			print_error_no_file_or_dir(input->path);
		if (!input->exist && input->read)
			print_error_no_permission(input->path);
		if (input->is_dir)
			print_error_is_a_directory(input->path);
	}
	if (output)
	{
		if (output->write)
			print_error_no_permission(output->path);
		if (output->is_dir)
			print_error_is_a_directory(output->path);
	}
}
int	print_command_error(t_file *program, t_file *infile, t_file *outfile)
{
	if ((infile && infile->read) || (outfile && outfile->write))
		return (1);
	if (program->exist)
		return (ft_putstr_fd("minishell: cmd not found: ", 2),
			ft_putstr_fd(program->path, 2), ft_putstr_fd("\n", 2), 127);
	else
		return (ft_putstr_fd("minishell: no rights: ", 2),
			ft_putstr_fd(program->path, 2), ft_putstr_fd("\n", 2), 126);
}