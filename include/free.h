/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:00:38 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 19:22:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	free_cmds(t_cmd *cmds);
void	free_tokens(t_token *tokens);
void	free_and_set_to_next_commands(t_cmd **cmds);
void	free_child(t_pipex *pipex);

#endif