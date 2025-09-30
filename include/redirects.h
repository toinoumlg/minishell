/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:46:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/30 12:32:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "minishell.h"

void	set_dup2(t_minishell *minishell);
void	dup2_infile(t_file *infile, t_minishell *minishell);
void	dup2_outfile(t_file *outfile, t_minishell *minishell);
void	dup2_append_file(t_file *append_file, t_minishell *minishell);
void	dup2_here_doc(t_file *here_doc_file, t_minishell *minishell);
void	dup2_pipes(int (*pipe_fds)[2], int size, int i, t_minishell *minishell);
void	dup2_std_copy(t_minishell *minishell);
void	dup_std_copy(t_minishell *minishell);

void	create_files(t_minishell *minishell);

int		set_here_doc(t_file *here_doc_file, t_minishell *minishell);
void	expand_here_doc(char **read_line, t_minishell *minishell);
void	close_here_doc(t_file *redirects);

void	do_pipe(t_minishell *minishell);
void	exit_on_eof(char *lim);
void	close_pipes(int (*pipe_fds)[2], int size, int i);
void	close_open_fds(t_minishell *minishell);

#endif