/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_string.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:18:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/16 19:50:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_EXPAND_STRING_H
# define TOKEN_EXPAND_STRING_H

# include "minishell.h"

int	expand_string(t_token *token, t_minishell *minishell);

#endif