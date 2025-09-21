/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 08:43:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parser/tokens/token_utils.h"
#include "token_free.h"
#include <stdlib.h>
#include <string.h>

static t_token	*get_operator_token(t_token *tokens, int j)
{
	int	i;

	i = 0;
	while (i++ < j && tokens)
		tokens = tokens->next;
	return (tokens);
}

static t_file	*new_file(t_minishell *minishell)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		exit_perror(minishell, "malloc ");
	memset(new, 0, sizeof(t_file));
	return (new);
}

t_file	*set_file(t_minishell *minishell, int j)
{
	t_file	*new;
	t_token	*tmp;

	new = new_file(minishell);
	tmp = get_operator_token(minishell->tokens, j);
	new->path = ft_strdup(tmp->next->string);
	if (!new->path)
	{
		free(new);
		exit_perror(minishell, "malloc ");
	}
	if (tmp->type == here_doc)
	{
		if (tmp->next->type == word)
			new->type = here_doc_word;
		else
			new->type = here_doc_quote;
	}
	else
		new->type = tmp->type;
	free_i_token(&minishell->tokens, j);
	free_i_token(&minishell->tokens, j);
	return (new);
}
