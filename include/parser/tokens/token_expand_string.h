/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_string.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:18:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 08:05:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_EXPAND_STRING_H
# define TOKEN_EXPAND_STRING_H

# include "minishell.h"

int		expand_string(t_token *token, t_minishell *minishell);
t_envp	*get_env_and_update_str(int *i, char *str, t_minishell *minishell);
#endif