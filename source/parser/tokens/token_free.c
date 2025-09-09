/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 19:56:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/tokens/token_free.h"
#include "parser/tokens/token_utils.h"
#include <stdlib.h>

void	free_first_token(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	next = tmp->next;
	if (tmp->string)
		free(tmp->string);
	free(tmp);
	*tokens = next;
}

void	free_i_token(t_token **tokens, int i)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*previous;
	t_token	*next;
	int		j;

	tmp = *tokens;
	if (!tmp)
		return ;
	if (i == 0)
		return (free_first_token(tokens));
	j = -1;
	head = tmp;
	while (++j < i - 1)
		tmp = tmp->next;
	previous = tmp;
	tmp = tmp->next;
	next = tmp->next;
	if (tmp->string)
		free(tmp->string);
	free(tmp);
	previous->next = next;
	*tokens = head;
}

void	free_pipe(t_token **tokens)
{
	t_token	*next;
	t_token	*tmp;

	tmp = *tokens;
	if (tmp && tmp->type == is_pipe)
	{
		next = tmp->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
		*tokens = next;
	}
}

void	free_tokens_from_args(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (!is_end_of_command(tmp))
	{
		next = tmp->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
		tmp = next;
	}
	*tokens = tmp;
}
