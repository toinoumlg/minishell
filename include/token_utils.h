/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:36:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 16:24:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include "minishell.h"

int		is_operator(char read_c);
int		get_word_size(char **read_line);
int		is_metacharacter(char c);
int		is_quote(char read_c);

void	fret_enum_tokens(t_token *tokens);

#endif