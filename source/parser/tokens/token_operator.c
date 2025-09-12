/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:32:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 19:37:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_list.h"
#include "token_utils.h"

t_enum_token	get_operator_type(char *line)
{
	if (*line && *(line + 1))
	{
		if (*line == '>')
		{
			if (!is_operator(*(line + 1)))
				return (output);
			if (*(line + 1) == '>' && !is_operator(*(line + 2)))
				return (append_file);
		}
		if (*line == '<')
		{
			if (!is_operator(*(line + 1)))
				return (input);
			if (*(line + 1) == '<' && !is_operator(*(line + 2)))
				return (here_doc);
		}
		if (*line == '|' && *(line + 1) != '|')
			return (is_pipe);
	}
	return (0);
}

void	set_operator_string(char **read_line, t_minishell *minishell,
		t_token *new)
{
	int	size;

	new->string = ft_strdup(*read_line);
	if (!new->string)
	{
		free(new);
		exit(free_minishell(minishell));
	}
	if (new->type == append_file || new->type == here_doc)
		size = 2;
	else
		size = 1;
	new->string[size] = 0;
	*read_line = *read_line + size;
}

int	add_operator_token(char **read_line, t_minishell *minishell, int *was_space)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	new_token->type = get_operator_type(*read_line);
	if (!new_token->type)
		return (1);
	set_operator_string(read_line, minishell, new_token);
	new_token->separated_by_space = *was_space;
	*was_space = 0;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}
