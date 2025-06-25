/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:10:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:11:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_UTILS_H
# define FREE_UTILS_H

# include "minishell.h"
void	free_array(char **args);
void	free_tokens(t_token *tokens);
void	free_file(t_file *file);
void	free_cmd(t_cmd *cmd);
#endif