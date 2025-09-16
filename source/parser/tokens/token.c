/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/16 20:27:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parse_error.h"
#include "token_expand.h"
#include "token_free.h"
#include "token_list.h"
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
	return ((cur->type == word || cur->type == word_expanded
			|| cur->type == simple_quote || cur->type == double_quote)
		&& (next->type == word || next->type == word_expanded
			|| next->type == simple_quote || next->type == double_quote));
}

char	*merge_token(char *s1, char *s2, t_minishell *minishell)
{
	int		size;
	char	*merged;
	int		i;
	int		j;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	merged = malloc(sizeof(char) * size);
	if (size > 0 && !merged)
		exit_perror(minishell, "malloc");
	if (!size && !merged)
		return (NULL);
	while (s1[i])
	{
		merged[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		merged[i + j] = s2[j];
		j++;
	}
	merged[i + j] = 0;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (merged);
}

static void	merge_adjacent_tokens(t_minishell *minishell)
{
	t_token	*cur;
	t_token	*next;

	cur = minishell->tokens;
	while (cur && cur->next)
	{
		next = cur->next;
		if (need_merge(cur, next))
		{
			cur->string = merge_token(cur->string, next->string, minishell);
			cur->next = next->next;
			free(next);
		}
		else
			cur = cur->next;
	}
}

void	add_space_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	if (!new_token)
		exit_perror(minishell, "malloc");
	new_token->type = space;
	append_new_token(&minishell->tokens, new_token);
}

static int	is_a_redirect(t_enum_token type)
{
	return (type == here_doc || type == append_file || type == output
		|| type == input);
}

int	check_valid_pipes(t_token *tokens)
{
	while (tokens)
	{
		while (tokens->type == space)
			tokens = tokens->next;
		if (!tokens)
			return (0);
		if (is_a_redirect(tokens->type))
		{
			tokens = tokens->next;
			while (tokens && tokens->type == space)
				tokens = tokens->next;
			if (!tokens || tokens->type == is_pipe)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	check_valid_redirects(t_token *tokens)
{
	while (tokens)
	{
		while (tokens->type == space)
			tokens = tokens->next;
		if (!tokens)
			return (0);
		if (is_a_redirect(tokens->type))
		{
			tokens = tokens->next;
			while (tokens && tokens->type == space)
				tokens = tokens->next;
			if (!tokens || (tokens->type != double_quote
				&& tokens->type != simple_quote && tokens->type != word))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	get_tokens_list(char **parse_error, t_minishell *minishell)
{
	memset(&minishell->tokens, 0, sizeof(t_token *));
	while (**parse_error)
	{
		if (**parse_error == ';' || **parse_error == '\\')
			return (1);
		else if (is_quote(**parse_error) && extract_quoted_string(parse_error,
				**parse_error, minishell))
			return (1);
		else if (is_operator(**parse_error) && add_operator_token(parse_error,
				minishell))
			return (1);
		else if (**parse_error == ' ' || **parse_error == '\t')
		{
			while (**parse_error == ' ' || **parse_error == '\t')
				(*parse_error)++;
			add_space_token(minishell);
		}
		else if (pick_word(parse_error, minishell))
			return (1);
	}
	return (check_valid_redirects(minishell->tokens)
		+ check_valid_pipes(minishell->tokens));
}

void	remove_tokens(t_minishell *minishell)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == space || tokens->type == space_expanded
			|| ((tokens->type == word || tokens->type == word_expanded)
				&& !ft_strlen(tokens->string)))
			return (free_i_token(&minishell->tokens, i),
				remove_tokens(minishell));
		i++;
		tokens = tokens->next;
	}
}

void	generate_tokens(t_minishell *minishell)
{
	char	*parse_error;

	parse_error = minishell->read_line;
	if (get_tokens_list(&parse_error, minishell))
		return (parsing_error(parse_error, minishell));
	if (!minishell->tokens)
		return (free_empty_prompt(minishell));
	expand(minishell);
	merge_adjacent_tokens(minishell);
	remove_tokens(minishell);
	if (minishell->read_line)
	{
		free(minishell->read_line);
		minishell->read_line = NULL;
	}
}
