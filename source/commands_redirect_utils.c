/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:02:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_utils.h"
#include "token_free.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

static t_token	*get_operator_token(t_token **tokens, int j)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *tokens;
	while (i++ < j && tmp)
		tmp = tmp->next;
	return (tmp);
}

static t_file	*new_file(void)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_file));
	return (new);
}

t_file	*set_file(t_token **tokens, int j)
{
	t_file	*new;
	t_token	*tmp;

	tmp = *tokens;
	if (!tmp->next)
		return (NULL);
	new = new_file();
	if (!new)
		return (NULL);
	tmp = get_operator_token(tokens, j);
	new->path = ft_strdup(tmp->next->string);
	if (!new->path)
		return (free(new), NULL);
	new->type = tmp->type;
	new->next = NULL;
	free_i_token(tokens, j);
	free_i_token(tokens, j);
	return (new);
}
