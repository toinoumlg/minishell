/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:45:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:00:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

void	append_new_command(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = *cmds;
	head = tmp;
	if (!tmp)
	{
		*cmds = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*cmds = head;
	return ;
}

t_cmd	*set_new_command(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_cmd));
	return (new);
}
