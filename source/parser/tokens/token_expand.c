/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 06:46:20 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_expand_string.h"
#include "token_free.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	insert_token(char *start, t_token *token, t_minishell *minishell,
		t_enum_token type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_perror(minishell, "malloc");
	memset(new, 0, sizeof(t_token));
	if (type == word_expanded)
	{
		new->string = ft_strdup(start);
		if (!new->string)
			return (free(new), exit_perror(minishell, "malloc"));
	}
	new->type = type;
	while (token->next && (token->next->type == word_expanded
			|| token->next->type == space_expanded))
		token = token->next;
	if (token->next)
		new->next = token->next;
	token->next = new;
}

void	expand_tokens(t_token *token, t_minishell *minishell)
{
	int		i;
	char	c;
	char	*start;

	i = 0;
	while (token->string[i])
	{
		if (token->string[i] == ' ' || token->string[i] == '\t')
		{
			while (token->string[i] == ' ' || token->string[i] == '\t')
				i++;
			insert_token(NULL, token, minishell, space_expanded);
		}
		start = &token->string[i];
		while (token->string[i] && token->string[i] != ' '
			&& token->string[i] != '\t')
			i++;
		c = token->string[i];
		token->string[i] = 0;
		insert_token(start, token, minishell, word_expanded);
		token->string[i] = c;
	}
	*token->string = 0;
}

// skips the expand when it's a here-doc delimiter
t_token	*get_next_expand(t_token *tokens)
{
	int	was_here_doc;

	was_here_doc = 0;
	while (tokens)
	{
		while (tokens && tokens->type != word && tokens->type != double_quote)
		{
			if (tokens->type == here_doc)
				was_here_doc = 1;
			tokens = tokens->next;
		}
		if (was_here_doc)
		{
			if (!tokens)
				return (NULL);
			tokens = tokens->next;
			was_here_doc = 0;
		}
		else
			return (tokens);
	}
	return (NULL);
}

void	expand(t_minishell *minishell)
{
	t_token	*tokens;

	tokens = minishell->tokens;
	while (tokens)
	{
		tokens = get_next_expand(tokens);
		if (!tokens)
			break ;
		if (expand_string(tokens, minishell) && tokens->type == word)
			expand_tokens(tokens, minishell);
		tokens = tokens->next;
	}
}
