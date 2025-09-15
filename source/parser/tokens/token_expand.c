/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 18:56:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_expand_utils.h"
#include "token_free.h"
#include <stdio.h>
#include <stdlib.h>

void	expand(int *i, t_token *token, t_minishell *minishell)
{
	char	*str;

	str = ft_strdup(token->string + *i + 1);
	token->string[*i] = 0;
	if (!str)
		exit_perror(minishell, "malloc");
	else if (!*str && token->next && (token->next->type == simple_quote
			|| token->next->type == double_quote))
		return (free(str));
	else if (!*str || *str == ' ')
	{
		token->string[*i] = '$';
		(*i)++;
	}
	else if (*str == '$')
		*i += expand_pid(str, token, minishell);
	else if (*str == '?')
		*i += expand_last_value(str, token, minishell);
	else
		*i += expand_env(str, token, minishell);
	free(str);
}

t_token	*get_next_token(t_token *token)
{
	if (!token->next || !token->next->next)
		return (NULL);
	token = token->next;
	while (token->type == space)
		token = token->next;
	token = token->next;
	while (token && (token->type != is_pipe || token->type != space))
		token = token->next;
	return (token);
}

void	expand_tokens(t_minishell *minishell)
{
	t_token	*tokens;
	int		i;

	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == here_doc)
			tokens = get_next_token(tokens);
		if (!tokens)
			break ;
		if (tokens->type == word || tokens->type == double_quote)
		{
			i = 0;
			while (tokens->string[i])
			{
				if (tokens->string[i] == '$')
					expand(&i, tokens, minishell);
				i++;
			}
		}
		tokens = tokens->next;
	}
}
