/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:28:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 22:53:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <string.h>

int	add_string_to_token(char *start, int i, t_token *new)
{
	new->string = ft_strdup(start);
	if (!new->string)
		return (1);
	new->string[i] = 0;
	return (0);
}

t_token	*set_new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_token));
	return (new);
}

void	append_new_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;
	t_token	*head;
	int		i;

	i = 0;
	tmp = *tokens;
	head = tmp;
	if (!tmp)
	{
		new->pos = i;
		*tokens = new;
		return ;
	}
	while (tmp->next && ++i)
		tmp = tmp->next;
	++i;
	tmp->next = new;
	new->pos = i;
	*tokens = head;
	return ;
}
