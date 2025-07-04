/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 20:47:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "token_list.h"
#include "token_utils.h"

int	get_quoted_string_size(char quote, char **read_line)
{
	int	i;

	i = 0;
	(*read_line)++;
	while (**read_line != quote && ++i)
		(*read_line)++;
	(*read_line)++;
	return (i + 1);
}

int	extract_quoted_string(char **read_line, char quote, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;

	i = 0;
	new_token = set_new_token(minishell);
	start = *read_line;
	i = get_quoted_string_size(quote, read_line);
	if (quote == '\'')
	{
		new_token->type = simple_quote;
		add_string_to_token(start, i + 1, new_token, minishell);
	}
	else
	{
		new_token->type = double_quote;
		add_string_to_token(start, 1 + i, new_token, minishell);
	}
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
		return (0);
	i = get_word_size(read_line);
	if (i <= 0)
		return (1);
	new_token = set_new_token(minishell);
	add_string_to_token(start, i, new_token, minishell);
	new_token->type = word;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}
