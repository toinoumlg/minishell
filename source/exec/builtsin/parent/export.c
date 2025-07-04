/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 21:11:46 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"

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

void	my_export(t_minishell *minishell)
{
	t_envp	*new_envp;
	char	*equal_sign;
	int		i;

	i = 1;
	if (!minishell->envp || !minishell->cmds->args[1])
	{
		minishell->pids[minishell->i] = -2;
		return ;
	}
	while (minishell->cmds->args[i])
	{
		equal_sign = ft_strchr(minishell->cmds->args[i] + 1, '=');
		if (ft_strlen(equal_sign + 1) < 1)
		{
			minishell->pids[minishell->i] = -2;
			return ;
		}
		new_envp = set_new_envp(minishell->cmds->args[i++]);
		if (!new_envp)
			exit(1);
		if (index_in_envp(new_envp->name, minishell->envp) >= 0)
			free_envp(new_envp);
		else
			append_new_envp(&minishell->envp, new_envp);
	}
}
