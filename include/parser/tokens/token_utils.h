/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:36:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 14:15:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include "minishell.h"

int	is_space(char c);
int	is_quote(char c);
int	is_operator(char c);
int	get_word_size(char **p);
int	get_quoted_string_size(char quote, char **line);

#endif