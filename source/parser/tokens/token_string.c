/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 13:10:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "parse_error.h"
#include "parser/tokens/token_utils.h"
#include "token_list.h"
#include <stdlib.h>

static int	get_word_size(char **p)
{
	int		n;
	char	*ptr;

	n = 0;
	ptr = *p;
	while (*ptr && !is_space(*ptr) && !is_operator(*ptr) && !is_quote(*ptr))
	{
		if (*ptr == ';' || *ptr == '\\')
		{
			*p = ptr;
			return (-1);
		}
		ptr++;
		n++;
	}
	*p = ptr;
	return (n);
}

static int	get_quoted_string_size(char quote, char **line)
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = *line;
	while (*ptr && *ptr != quote)
	{
		len++;
		ptr++;
	}
	if (*ptr == quote)
	{
		ptr++;
		*line = ptr;
		return (len);
	}
	return (-1);
}

int	extract_quoted_string(char **read_line, char quote, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;
	char	c;

	(*read_line)++;
	start = *read_line;
	i = get_quoted_string_size(quote, read_line);
	if (i < 0)
		return (1);
	new_token = set_new_token(minishell);
	append_new_token(&minishell->tokens, new_token);
	c = start[i];
	start[i] = 0;
	add_string_to_token(start, new_token, minishell);
	start[i] = c;
	if (quote == '\'')
		new_token->type = simple_quote;
	else if (quote == '"')
		new_token->type = double_quote;
	return (0);
}

int	pick_word(char **read_line, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;
	char	c;

	start = *read_line;
	if (!**read_line || is_space(**read_line) || is_operator(**read_line)
		|| is_quote(**read_line))
		return (0);
	i = get_word_size(read_line);
	if (i <= 0)
		return (1);
	new_token = set_new_token(minishell);
	append_new_token(&minishell->tokens, new_token);
	c = start[i];
	start[i] = 0;
	add_string_to_token(start, new_token, minishell);
	start[i] = c;
	new_token->type = word;
	return (0);
}
