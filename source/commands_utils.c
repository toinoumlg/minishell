/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:50:31 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 16:24:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	delett_enum_token(t_token **tokens, int j)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*previous;
	t_token	*next;
	int		i;

	i = -1;
	tmp = *tokens;
	head = tmp;
	while (++i < j - 1)
		tmp = tmp->next;
	previous = tmp;
	tmp = tmp->next;
	next = tmp->next;
	free(tmp->string);
	free(tmp);
	previous->next = next;
	*tokens = head;
}

int	is_end_of_command(t_token *token)
{
	if (!token || token->type == is_pipe)
		return (1);
	else
		return (0);
}
