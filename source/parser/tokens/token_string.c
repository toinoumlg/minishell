/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/09 16:34:05 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token_list.h"
#include "parser/tokens/token_utils.h"
#include "parse_error.h"
#include <stdlib.h>


t_token *extract_quoted_string(char **read_line, char quote, t_minishell *minishell)
{
    t_token    *new_token;
    char    *start;
    int        i;

    new_token = set_new_token(minishell);
    if (!new_token)
        return (NULL);
    (*read_line)++;
    start = *read_line;
    i = get_quoted_string_size(quote, read_line);
    if (i < 0)
        return (NULL);
    add_string_to_token(start, i, new_token, minishell);
    if (quote == '\'')
        new_token->type = simple_quote;
    else if (quote == '"')
        new_token->type = double_quote;
    return (append_new_token(&minishell->tokens, new_token));
}

t_token *pick_word(char **read_line, t_minishell *minishell)
{
    t_token    *new_token;
    char    *start;
    int        i;

    start = *read_line;
    if (!**read_line)
        return (NULL);
    i = get_word_size(read_line);
    if (i <= 0)
        return (NULL);
    new_token = set_new_token(minishell);
    add_string_to_token(start, i, new_token, minishell);
    new_token->type = word;
    return (append_new_token(&minishell->tokens, new_token));
}
