/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/08 06:57:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	extract_quoted_string(char **read_line, char quote, t_token **tokens)
{
	t_token	*new;
	char	*start;
	int		i;

	i = 0;
	new = set_new_token();
	if (!new)
		return (1);
	start = *read_line;
	i = get_quoted_string_size(quote, read_line);
	if (quote == '\'')
	{
		new->type = simple_quote;
		if (add_string_to_token(start, i + 1, new))
			return (1);
	}
	else
	{
		new->type = double_quote;
		if (add_string_to_token(start, 1 + i, new))
			return (1);
	}
	append_new_token(tokens, new);
	return (0);
}

int	pick_word(char **read_line, t_token **tokens)
{
	t_token *new;
	char *start;
	int i;

	start = *read_line;
	if (!**read_line)
		return (0);
	i = get_word_size(read_line);
	new = set_new_token();
	if (!new || i <= 0 || add_string_to_token(start, i, new))
		return (1);
	new->type = word;
	append_new_token(tokens, new);
	return (0);
}