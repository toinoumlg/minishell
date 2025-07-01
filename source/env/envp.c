/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:41:48 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 18:57:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_no_input.h"
#include "libft.h"
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
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_envp));
	new->line = ft_strdup(envp_line);
	if (!new->line)
		return (free(new), NULL);
	new->name = set_name(envp_line);
	if (!new->name)
		return (free(new->line), free(new), NULL);
	new->value = set_value(envp_line);
	if (!new->value)
		return (free(new->name), free(new->line), free(new), NULL);
	return (new);
}

void	append_new_envp(t_envp **envp_struct, t_envp *new)
{
	t_envp	*tmp;
	t_envp	*head;

	tmp = *envp_struct;
	head = tmp;
	if (!tmp)
	{
		*envp_struct = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*envp_struct = head;
}

void	set_envp(t_envp **envp_struct, char **envp)
{
	int i;
	t_envp *new;

	i = 0;
	if (!envp)
		return (set_envp_no_input(envp_struct));
	while (envp[i])
	{
		new = set_new_envp(envp[i++]);
		if (!new)
			return ;
		append_new_envp(envp_struct, new);
	}
}