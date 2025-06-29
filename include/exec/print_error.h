/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:40:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 06:08:53 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ERROR_H
# define PRINT_ERROR_H

# include "minishell.h"

int		print_command_error(t_file *program, t_file *error);
void	print_error_file(t_file *error);

#endif