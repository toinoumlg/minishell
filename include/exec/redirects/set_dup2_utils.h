/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:37 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 13:41:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_DUP2_UTILS_H
# define SET_DUP2_UTILS_H

# include "minishell.h"

void	dup2_infile(t_file *infile, t_minishell *minishell);
void	dup2_outfile(t_file *outfile, t_minishell *minishell);
void	dup2_append_file(t_file *append_file, t_minishell *minishell);
void	dup2_here_doc(t_file *here_doc_file, t_minishell *minishell);

#endif