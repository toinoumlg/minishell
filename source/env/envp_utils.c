/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:58:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 10:13:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*set_name(char *line, t_minishell *minishell)
{
	char	*name;
	int		i;

	i = -1;
	name = ft_strdup(line);
	if (!name)
		exit_perror(minishell, "malloc :");
	while (line[++i])
	{
		if (line[i] == '=')
		{
			name[i] = 0;
			return (name);
		}
	}
	return (name);
}

char	*set_value(char *line, t_minishell *minishell)
{
	char	*value;

	value = ft_strchr(line, '=');
	if (value)
	{
		if (ft_strlen(value + 1) > 0)
		{
			value = ft_strdup(value + 1);
			if (!value)
				exit_perror(minishell, "malloc :");
		}
		else
		{
			value = ft_strdup("");
			if (!value)
				exit_perror(minishell, "malloc :");
		}
		return (value);
	}
	else
		return (NULL);
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

t_envp	*set_new_envp(char *envp_line, t_minishell *minishell)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		exit_perror(minishell, "malloc :");
	memset(new_envp, 0, sizeof(t_envp));
	new_envp->line = ft_strdup(envp_line);
	if (!new_envp->line)
		exit_perror(minishell, "malloc :");
	new_envp->name = set_name(envp_line, minishell);
	new_envp->value = set_value(envp_line, minishell);
	return (new_envp);
}

// Return a pointer to envp struct that match specified name.
// Return NULL if not in environnement.
t_envp	*find_existing_envp(char *name, t_envp *envp)
{
	int	i;

	i = 0;
	if (!envp || !name)
		return (NULL);
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (envp);
		i++;
		envp = envp->next;
	}
	return (NULL);
}
