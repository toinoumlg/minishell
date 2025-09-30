/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 19:55:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "parser/token.h"
#include <stdlib.h>

void	remove_first_token(t_token **tokens, t_token **to_remove_add)
{
	t_token	*to_remove;

	to_remove = *to_remove_add;
	if (to_remove->next)
	{
		*tokens = to_remove->next;
		*to_remove_add = to_remove->next;
	}
	else
	{
		*tokens = NULL;
		*to_remove_add = NULL;
	}
	if (to_remove->string)
		free(to_remove->string);
	free(to_remove);
}

void	remove_token(t_token **tokens, t_token **to_remove_add)
{
	t_token	*tmp;
	t_token	*to_remove;

	to_remove = *to_remove_add;
	tmp = *tokens;
	if (tmp == to_remove)
		return (remove_first_token(tokens, to_remove_add));
	while (tmp->next && tmp->next != to_remove)
		tmp = tmp->next;
	if (to_remove->next)
	{
		tmp->next = to_remove->next;
		*to_remove_add = to_remove->next;
	}
	else
	{
		tmp->next = NULL;
		*to_remove_add = NULL;
	}
	if (to_remove->string)
		free(to_remove->string);
	free(to_remove);
}

void	remove_pipe(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp && tmp->type == is_pipe)
	{
		*tokens = tmp->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
	}
}

void	remove_args(t_token **tokens)
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
