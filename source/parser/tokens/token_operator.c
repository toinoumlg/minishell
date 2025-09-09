/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:32:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 19:55:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_list.h"
#include "token_utils.h"

t_enum_token	get_operator_type(char **line)
{
	char	*ptr;

	ptr = *line;
	if (*ptr && *(ptr + 1))
	{
		if (*ptr == '>')
		{
			if (!is_operator(*(ptr + 1)))
				return (output);
			if (*(ptr + 1) == '>' && !is_operator(*(ptr + 2)))
				return (append_file);
		}
		if (*ptr == '<')
		{
			if (!is_operator(*(ptr + 1)))
				return (input);
			if (*(ptr + 1) == '<' && !is_operator(*(ptr + 2)))
				return (here_doc);
		}
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
		exit(free_on_exit_error(minishell));
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
	new_token->type = get_operator_type(read_line);
	if (!new_token->type)
		return (1);
	set_operator_string(read_line, minishell, new_token);
	new_token->separated_by_space = *was_space;
	*was_space = 0;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}
