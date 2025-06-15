/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:00:38 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 18:25:25 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	free_cmds(t_cmd *cmds);
void	free_array(char **args);
void	free_tokens(t_token *tokens);
void	free_get_token_list(char *read_line, t_token *tokens);
void	free_set_commands(char *read_line, t_token *tokens, t_cmd *cmds);
void	free_and_set_to_next_commands(t_cmd **cmds);
void	free_child(t_pipex *pipex);

#endif