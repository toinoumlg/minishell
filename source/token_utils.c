/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 23:12:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->string)
			free(tokens->string);
		free(tokens);
		tokens = tmp;
	}
}

int	is_metacharacter(char c)
{
	if (c == ' ' || c == '	' || c == '\n' || c == '|' || c == '&' || c == ';'
		|| c == '(' || c == ')' || c == '<' || c == '>' || c == 0)
		return (1);
	else
		return (0);
}

int	get_word_size(char **read_line)
{
	int	i;

	i = 0;
	while (!is_metacharacter(**read_line) && ++i)
		(*read_line)++;
	return (i);
}

int	is_operator(char read_c)
{
	if (read_c == '<' || read_c == '>' || read_c == '|')
		return (1);
	else
		return (0);
}

int	is_quote(char read_c)
{
	if (read_c == '"' || read_c == '\'')
		return (1);
	else
		return (0);
}
