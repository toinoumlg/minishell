/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:45:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 15:02:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <stdlib.h>
#include <string.h>

void	append_new_command(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = *cmds;
	head = tmp;
	if (!tmp)
	{
		*cmds = new_cmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	*cmds = head;
	return ;
}

t_cmd	*set_new_command(t_minishell *minishell)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_perror(minishell, "malloc ");
	memset(new, 0, sizeof(t_cmd));
	return (new);
}
