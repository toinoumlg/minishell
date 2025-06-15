/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:40:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 11:41:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ERROR_H
# define PRINT_ERROR_H

# include "minishell.h"

int		print_command_error(t_file *program, t_file *infile, t_file *outfile);
void	print_error_file(t_file *input, t_file *output);

#endif