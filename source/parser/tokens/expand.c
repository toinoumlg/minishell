/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 14:46:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "parser/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	Create and insert a new_token with provided type and string
	Marked as word_expanded or space_expand
	Inserted after existing expanded tokens	*/
static void	insert_token(char *start, t_token *token, t_minishell *minishell,
		t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_perror(minishell, "malloc");
	ft_memset(new, 0, sizeof(t_token));
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

/*	Parse the string created in expand_string and splits it into new tokens
	New_tokens are inserted after the token itself
	Token string is set to 0 to get removed after	*/
static void	expand_tokens(t_token *token, t_minishell *minishell)
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

/*	Skips all non-desired tokens for expand
	As well as if it's a limiter for here_doc	*/
static t_token	*get_next_expand(t_token *tokens)
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

/*	Parse token string and expands when encountering '$'
	Sets where '$' position to null for string reconstruction	*/
static int	expand_string(t_token *token, t_minishell *minishell)
{
	int	i;
	int	expanded;

	i = 0;
	expanded = 0;
	while (token->string[i])
	{
		if (token->string[i] == '$')
		{
			token->string[i] = 0;
			handle_expansion(&i, token, minishell);
			expanded++;
		}
		i++;
	}
	return (expanded);
}

/*	Expand all word and double_quote tokens with variables
	If it's a word token expand his string into new tokens after itself	*/
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
