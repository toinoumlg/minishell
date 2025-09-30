/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:56:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:03:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "parser/token.h"
#include <stdlib.h>

void	add_space(char **parse_error, t_minishell *minishell)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	new_token->type = space;
	append_new_token(&minishell->tokens, new_token);
	while (is_space(**parse_error))
		(*parse_error)++;
}

static int	get_word_size(char **parse_error)
{
	int		i;
	char	*str;

	i = 0;
	str = *parse_error;
	while (str[i] && !is_space(str[i]) && !is_operator(str[i])
		&& !is_quote(str[i]))
	{
		if (str[i] == ';' || str[i] == '\\')
		{
			*parse_error = str + i;
			return (-1);
		}
		i++;
	}
	*parse_error = str + i;
	return (i);
}

static int	get_quoted_string_size(char **parse_error, char quote)
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = *parse_error;
	while (*ptr && *ptr != quote)
	{
		len++;
		ptr++;
	}
	*parse_error = ptr;
	if (*ptr == quote)
	{
		ptr++;
		*parse_error = ptr;
		return (len);
	}
	return (-1);
}

int	add_quoted_string(char **parse_error, char quote, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;
	char	c;

	(*parse_error)++;
	start = *parse_error;
	i = get_quoted_string_size(parse_error, quote);
	if (i < 0)
		return (1);
	new_token = set_new_token(minishell);
	append_new_token(&minishell->tokens, new_token);
	c = start[i];
	start[i] = 0;
	new_token->string = ft_strdup(start);
	if (!new_token->string)
		exit_perror(minishell, "malloc");
	start[i] = c;
	if (quote == '\'')
		new_token->type = simple_quote;
	else if (quote == '"')
		new_token->type = double_quote;
	return (0);
}

int	add_word(char **parse_error, t_minishell *minishell)
{
	t_token	*new_token;
	char	*start;
	int		i;
	char	c;

	start = *parse_error;
	if (!**parse_error || is_space(**parse_error) || is_operator(**parse_error)
		|| is_quote(**parse_error))
		return (0);
	i = get_word_size(parse_error);
	if (i <= 0)
		return (1);
	new_token = set_new_token(minishell);
	append_new_token(&minishell->tokens, new_token);
	c = start[i];
	start[i] = 0;
	new_token->string = ft_strdup(start);
	if (!new_token->string)
		exit_perror(minishell, "malloc");
	start[i] = c;
	new_token->type = word;
	return (0);
}
