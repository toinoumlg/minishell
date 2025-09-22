/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:00:38 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:09:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	free_array(char **args);
void	free_tokens(t_token *tokens);
void	free_file(t_file *file);
void	free_cmds(t_cmd *cmds);
void	free_and_set_to_next_commands(t_cmd **cmds);
int		free_envp(t_envp *envp);
int		free_minishell(t_minishell *minishell);
void	exit_perror(t_minishell *minishell, char *str);

#endif