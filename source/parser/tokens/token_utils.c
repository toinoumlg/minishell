/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/09 17:02:41 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/tokens/token_utils.h"
#include "parser/tokens/token_list.h"
#include <stdlib.h>

/* helpers de base */

int	is_end_of_command(t_token *token)
{
	if (token == NULL)
		return (1);
	if (token->type == is_pipe)
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

int	is_operator_char(char c)
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
	while (*ptr && !is_space(*ptr) && !is_operator_char(*ptr) && !is_quote(*ptr))
	{
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

int	get_operator_size(char **line)
{
	int		sz;
	char	*ptr;

	sz = 0;
	ptr = *line;
	if (*ptr == '|' || *ptr == '<' || *ptr == '>')
	{
		if (*ptr == '<' && *(ptr + 1) == '<')
		{
			ptr = ptr + 2;
			sz = 2;
		}
		else if (*ptr == '>' && *(ptr + 1) == '>')
		{
			ptr = ptr + 2;
			sz = 2;
		}
		else
		{
			ptr = ptr + 1;
			sz = 1;
		}
		*line = ptr;      /* ⬅️ avance le pointeur ! */
		return (sz);
	}
	return (0);
}

t_token	*add_operator_token(char **read_line, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		sz;

	new_token = set_new_token(minishell);
	if (!new_token)
		return (NULL);
	start = *read_line;

	/* set le type AVANT de bouger le pointeur (on lit sur start) */
	if (*start == '|')
		new_token->type = is_pipe;
	else if (*start == '<' && *(start + 1) == '<')
		new_token->type = here_doc;
	else if (*start == '>' && *(start + 1) == '>')
		new_token->type = append_file;
	else if (*start == '<')
		new_token->type = input;
	else if (*start == '>')
		new_token->type = output;

	sz = get_operator_size(read_line);              /* ⬅️ fait avancer *read_line */
	add_string_to_token(start, sz, new_token, minishell);
	return (append_new_token(&minishell->tokens, new_token));
}