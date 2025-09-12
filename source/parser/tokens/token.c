/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/12 09:16:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parse_error.h"
#include "token_expand.h"
#include "token_operator.h"
#include "token_string.h"
#include "token_utils.h"
#include <stdlib.h>
#include <string.h>

static void	free_empty_prompt(t_minishell *minishell)
{
	free(minishell->read_line);
	minishell->read_line = NULL;
	minishell->tokens = NULL;
	return ;
}

static int	need_merge(t_token *cur, t_token *next)
{
	return (!next->separated_by_space && (cur->type == word
			|| cur->type == simple_quote || cur->type == double_quote)
		&& (next->type == word || next->type == simple_quote
			|| next->type == double_quote));
}

static void	merge_adjacent_words(t_minishell *minishell)
{
	t_token	*cur;
	t_token	*next;
	char	*merged;

	cur = minishell->tokens;
	while (cur && cur->next)
	{
		next = cur->next;
		if (need_merge(cur, next))
		{
			merged = ft_strjoin(cur->string, next->string);
			if (!merged)
				exit_perror(minishell, "malloc ");
			free(cur->string);
			cur->string = merged;
			cur->next = next->next;
			free(next->string);
			free(next);
		}
		else
			cur = cur->next;
	}
}

static int	get_tokens_list(char **parse_error, t_minishell *minishell)
{
	int	was_space;

	memset(&minishell->tokens, 0, sizeof(t_token *));
	was_space = 1;
	while (**parse_error)
	{
		if (**parse_error == ';' || **parse_error == '\\')
			return (1);
		else if (is_quote(**parse_error) && extract_quoted_string(parse_error,
				**parse_error, minishell, &was_space))
			return (1);
		else if (is_operator(**parse_error) && add_operator_token(parse_error,
				minishell, &was_space))
			return (1);
		else if (**parse_error == ' ')
		{
			while (**parse_error == ' ')
				(*parse_error)++;
			was_space = 1;
		}
		else if (pick_word(parse_error, minishell, &was_space))
			return (1);
	}
	return (0);
}

void	generate_tokens(t_minishell *minishell)
{
	char	*parse_error;

	parse_error = minishell->read_line;
	if (get_tokens_list(&parse_error, minishell))
		return (parsing_error(parse_error, minishell));
	if (!minishell->tokens)
		return (free_empty_prompt(minishell));
	merge_adjacent_words(minishell);
	expand_tokens(minishell);
}
