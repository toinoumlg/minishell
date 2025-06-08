/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 22:57:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_STRING_H
#define TOKEN_STRING_H

#include "minishell.h"

int	pick_word(char **read_line, t_token **tokens);
int	extract_quoted_string(char **read_line, char quote, t_token **tokens);

#endif