/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/25 19:38:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

static char	*set_name(char *envp_line)
{
	char	*name;
	int		i;

	i = -1;
	name = ft_strdup(envp_line);
	if (!name)
		return (NULL);
	while (envp_line[++i])
	{
		if (envp_line[i] == '=')
		{
			name[i] = 0;
			return (name);
		}
	}
	free(name);
	return (NULL);
}

static char	*set_value(char *envp_line)
{
	while (*envp_line != '=')
		envp_line++;
	return (ft_strdup(++envp_line));
}

static t_envp	*set_new_envp(char *envp_line)
{
	t_envp	*new_envp;

	if (!ft_strchr(envp_line, '='))
		return (NULL);
	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	memset(new_envp, 0, sizeof(t_envp));
	new_envp->line = ft_strdup(envp_line);
	if (!new_envp->line)
		return (free(new_envp), NULL);
	new_envp->name = set_name(envp_line);
	if (!new_envp->name)
		return (free(new_envp->line), free(new_envp), NULL);
	new_envp->value = set_value(envp_line);
	if (!new_envp->value)
		return (free(new_envp->name), free(new_envp->line), free(new_envp),
			NULL);
	return (new_envp);
}

t_envp	*find_existing_envp(char *name, t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (envp);
		i++;
		envp = envp->next;
	}
	return (NULL);
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
			{
				free(existing->line);
				existing->line = new_envp->line;
				free(existing->value);
				existing->value = new_envp->value;
				free(existing->name);
				existing->name = new_envp->name;
				free(new_envp);
			}
			else
				append_new_envp(&minishell->envp, new_envp);
		}
	}
}
