/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/29 08:36:07 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse_error.h"
#include "parser/tokens/token_utils.h"
#include "token_check.h"
#include "token_list.h"
#include "token_operator.h"
#include "token_string.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int	add_space_token(char **parse_error, t_minishell *minishell)
{
	t_token	*new;

	new = set_new_token(minishell);
	if (!new)
		return (1);
	while (**parse_error == ' ')
	{
		(*parse_error)++;
	}
	new->type = space;
	new->string = ft_strdup(" ");
	append_new_token(&minishell->tokens, new);
	return (0);
}

int	get_tokens_list(char **parse_error, t_minishell *minishell)
{
	memset(&minishell->tokens, 0, sizeof(t_token *));
	while (**parse_error)
	{
		if (**parse_error == ' ')
			add_space_token(parse_error, minishell);
		else if (is_quote(**parse_error))
			extract_quoted_string(parse_error, **parse_error, minishell);
		else if (is_operator_char(**parse_error))
			add_operator_token(parse_error, minishell);
		else
			pick_word(parse_error, minishell);
	}
	return (0);
}
