/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 20:13:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	is_metacharacter(char c)
{
	if (c == ' ' || c == '	' || c == '\n' || c == '|' || c == '&' || c == ';'
		|| c == '(' || c == ')' || c == '<' || c == '>' || c == 0)
		return (1);
	else
		return (0);
}

int	is_end_of_command(t_token *token)
{
	if (!token || token->type == is_pipe)
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

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	else
		return (0);
}
