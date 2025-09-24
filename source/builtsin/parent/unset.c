/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 20:08:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include <stdio.h>

void	remove_first_envp(t_envp **envp, t_envp *to_unset)
{
	if (to_unset->next)
		*envp = to_unset->next;
	else
		*envp = NULL;
	if (to_unset->value)
		free(to_unset->value);
	free(to_unset->line);
	free(to_unset->name);
	free(to_unset);
}

void	remove_envp(t_envp **envp, t_envp *to_unset)
{
	t_envp	*tmp;

	tmp = *envp;
	if (tmp == to_unset)
		return (remove_first_envp(envp, to_unset));
	while (tmp->next && tmp->next != to_unset)
		tmp = tmp->next;
	if (to_unset->next)
		tmp->next = to_unset->next;
	else
		tmp->next = NULL;
	if (to_unset->value)
		free(to_unset->value);
	free(to_unset->line);
	free(to_unset->name);
	free(to_unset);
}

int	unset(t_minishell *minishell)
{
	int		i;
	t_envp	*to_unset;

	i = 1;
	while (minishell->cmds->args[i])
	{
		to_unset = find_existing_envp(minishell->cmds->args[i++],
				minishell->envp);
		if (to_unset)
			remove_envp(&minishell->envp, to_unset);
	}
	return (0);
}
