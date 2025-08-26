/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:41:48 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/26 19:57:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
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

t_envp	*set_new_envp(char *envp_line)
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

void	append_new_envp(t_envp **envp_struct, t_envp *new_envp)
{
	t_envp	*tmp;
	t_envp	*head;

	tmp = *envp_struct;
	head = tmp;
	if (!tmp)
	{
		*envp_struct = new_envp;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_envp;
	*envp_struct = head;
}

// Parse all then envp array and create a struct containing:
// char *line = full line of the variable
// char *name = left-side of the equal-sign
// char *value = right-side of the equal sign
void	set_envp(t_minishell *minishell, char **envp)
{
	int		i;
	t_envp	*new;

	memset(minishell, 0, sizeof(t_minishell));
	i = 0;
	while (envp[i])
	{
		new = set_new_envp(envp[i++]);
		if (!new)
			return ;
		append_new_envp(&minishell->envp, new);
	}
}
