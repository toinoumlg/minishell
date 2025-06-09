/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:45:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 15:58:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_args.h"
#include "commands_check.h"
#include "commands_redirect.h"
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

int	add_new_command(t_token **tokens, t_minishell *minishell)
{
	t_cmd	*new;

	if (check_for_duplicate(*tokens))
		return (1);
	new = set_new_command();
	if (pick_redirects(new, tokens))
		return (1);
	new->args = set_args(tokens);
	new->pipe_to_next = check_for_pipe(tokens);
	append_new_command(&minishell->cmds, new);
	return (0);
}

int	set_commands(t_token **tokens, t_minishell *minishell)
{
	while (*tokens)
		if (add_new_command(tokens, minishell))
			return (1);
	return (0);
}
