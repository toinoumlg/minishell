/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/29 08:23:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"
#include "parser/tokens/token_utils.h"
#include "token_list.h"
#include <stdlib.h>

int	extract_quoted_string(char **read_line, char quote, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;

	new_token = set_new_token(minishell);
	if (!new_token)
		return (1);
	(*read_line)++;
	start = *read_line;
	i = get_quoted_string_size(quote, read_line);
	if (i < 0)
		return (1);
	add_string_to_token(start, i, new_token, minishell);
	if (quote == '\'')
		new_token->type = simple_quote;
	else if (quote == '"')
		new_token->type = double_quote;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}

int	pick_word(char **read_line, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;

	start = *read_line;
	if (!**read_line)
		return (1);
	i = get_word_size(read_line);
	if (i <= 0)
		return (1);
	new_token = set_new_token(minishell);
	add_string_to_token(start, i, new_token, minishell);
	new_token->type = word;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}
