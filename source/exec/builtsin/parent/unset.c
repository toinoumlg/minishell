/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:12:21 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <stdio.h>

static void	delete_0_envp(t_envp *next, t_envp *head, t_envp **envp)
{
	next = head->next;
	head->next = NULL;
	free_envp(head);
	*envp = next;
}

static void	delete_i_envp(int index, t_envp **envp)
{
	t_envp	*next;
	t_envp	*tmp;
	t_envp	*head;
	t_envp	*prev;

	next = NULL;
	head = *envp;
	tmp = head;
	if (!index)
		return (delete_0_envp(next, head, envp));
	while (index--)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	next = tmp->next;
	prev->next = next;
	tmp->next = NULL;
	free_envp(tmp);
	*envp = head;
}

static int	index_in_envp(char *name, t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (i);
		i++;
		envp = envp->next;
	}
	return (-1);
}

void	unset(t_minishell *minishell)
{
	int	i;
	int	envp_index;

	i = 1;
	if (!minishell->envp || !minishell->cmds->args[1])
	{
		minishell->pids[minishell->i] = -1;
		return ;
	}
	while (minishell->cmds->args[i])
	{
		envp_index = index_in_envp(minishell->cmds->args[i++],
				minishell->envp);
		if (envp_index >= 0)
			delete_i_envp(envp_index, &minishell->envp);
	}
	minishell->pids[minishell->i] = -1;
}
