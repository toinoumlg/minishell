/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:49:53 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/09 15:23:49 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	print_tokens(t_token *tokens);
void	print_commands(t_cmd *cmds);
int		is_space(char c);
int		is_quote(char c);
int		is_operator_char(char c); /* si tu veux garder "is_operator", garde la même signature */
int		get_word_size(char **p);
int		get_quoted_string_size(char quote, char **line);
int		get_operator_size(char **line);

#endif
