/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:37 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:17:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_DUP2_UTILS_H
# define SET_DUP2_UTILS_H

# include "minishell.h"

int		dup2_infile(t_file *infile);
int		dup2_outfile(t_file *outfile);
int		dup2_append_file(t_file *append_file);
int		is_type_in_redirects(t_file *redirects, t_enum_token type);
void	exit_set_files_in_child(t_pipex *pipex);

#endif