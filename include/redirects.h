/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:46:32 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 08:03:58 by amalangu         ###   ########.fr       */
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

void	create_files(t_minishell *minishell);

void	set_here_doc(t_file *here_doc_file, t_minishell *minishell);
int		expand_env_here_doc(char *str,  char **read_line, t_minishell *minishell);
int		expand_last_status_here_doc(char *str, char **read_line,
			t_minishell *minishell);
int		expand_pid_here_doc(char *str, char **read_line,
			t_minishell *minishell);

void	do_pipe(t_minishell *minishell);

void	close_pipes(int (*pipe_fds)[2], int size, int i);

#endif