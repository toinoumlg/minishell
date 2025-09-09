/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 19:57:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "token_list.h"
#include "token_utils.h"
#include <stdlib.h>

/* helpers de base */

int	is_end_of_command(t_token *token)
{
	if (token == NULL || token->type == is_pipe)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/* parsing mots / quotes / opérateurs */

int	get_word_size(char **p)
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

int	get_quoted_string_size(char quote, char **line)
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
