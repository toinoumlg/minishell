/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/20 15:47:06 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_STRING_H
# define TOKEN_STRING_H

# include "minishell.h"

t_token *pick_word(char **read_line, t_minishell *minishell);
t_token *extract_quoted_string(char **read_line, char quote, t_minishell *minishell);

#endif