/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/26 19:42:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

void	update_values(t_envp *existing, t_envp *new)
{
	free(existing->line);
	existing->line = new->line;
	free(existing->value);
	existing->value = new->value;
	free(existing->name);
	existing->name = new->name;
	free(new);
}

void	my_export(t_minishell *minishell)
{
	t_envp	*new_envp;
	t_envp	*existing;
	int		i;

	i = 1;
	if (!minishell->envp || !minishell->cmds->args[1])
	{
		minishell->pids[minishell->i] = -2;
		return ;
	}
	while (minishell->cmds->args[i])
	{
		new_envp = set_new_envp(minishell->cmds->args[i++]);
		if (new_envp)
		{
			existing = find_existing_envp(new_envp->name, minishell->envp);
			if (existing)
				update_values(existing, new_envp);
			else
				append_new_envp(&minishell->envp, new_envp);
		}
	}
}
