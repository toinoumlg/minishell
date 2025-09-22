/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:30:47 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:29:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "parser/token.h"

static void	remove_empty(t_minishell *minishell)
{
	t_token	*tokens;

	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == space || tokens->type == space_expanded
			|| ((tokens->type == word || tokens->type == word_expanded)
				&& !ft_strlen(tokens->string)))
			remove_token(&minishell->tokens, &tokens);
		else
			tokens = tokens->next;
	}
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

	i = -1;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	merged = malloc(sizeof(char) * size);
	if (!merged)
		exit_perror(minishell, "malloc");
	while (s1 && s1[++i])
		merged[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		merged[i + j] = s2[j];
	merged[i + j] = 0;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (merged);
}

void	merge_adjacent(t_minishell *minishell)
{
	t_token	*tokens;
	t_token	*next;

	tokens = minishell->tokens;
	while (tokens && tokens->next)
	{
		next = tokens->next;
		if (need_merge(tokens, next))
		{
			tokens->string = merge_token(tokens->string, next->string,
					minishell);
			tokens->type = next->type;
			tokens->next = next->next;
			free(next);
		}
		else
			tokens = tokens->next;
	}
	remove_empty(minishell);
}
