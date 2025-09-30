/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:33:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 15:36:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	exec(t_minishell *minishell);
int		is_builtin_to_exec_in_parent(t_minishell *minishell);
void	underscore(t_minishell *minishell);

void	exit_child(t_minishell *minishell);
int		print_command_error(t_file *program, t_file *error);
void	print_error_file(t_file *error);

#endif