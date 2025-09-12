/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:43:59 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/12 09:46:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include "minishell.h"

int		get_envp_size(t_envp *envp);
char	**get_env(char *full_path);
void	dup_envp_array(t_minishell *minishell);
void	dup_env_array(t_minishell *minishell);

#endif