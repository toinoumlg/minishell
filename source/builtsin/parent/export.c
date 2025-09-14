/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 09:14:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_envp.h"
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

void	swap_string(char **array, int i, int j)
{
	char	*tmp;

	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void	sort_envp(char **envp)
{
	char	**envp_sorted;
	int		i;
	int		j;

	envp_sorted = envp;
	i = 0;
	if (!envp_sorted)
		return ;
	while (envp_sorted[i])
	{
		j = i + 1;
		while (envp_sorted[j])
		{
			if (ft_strncmp(envp_sorted[i], envp_sorted[j],
					ft_strlen(envp_sorted[i] + 1)) > 0)
				swap_string(envp_sorted, i, j);
			j++;
		}
		i++;
	}
	i = 0;
	while (envp_sorted[i])
	{
		if (ft_strncmp(envp_sorted[i], "_=", 2))
			printf("declare -x %s\n", envp_sorted[i]);
		i++;
	}
	return ;
}

void	print_sorted_envp(t_minishell *minishell)
{
	sort_envp(minishell->envp_array);
	minishell->pids[minishell->i] = -1;
}

static char	*set_name_export(char *envp_line)
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
	return (name);
}

static char	*set_value_export(char *envp_line)
{
	char	*value;

	value = ft_strchr(envp_line, '=');
	printf("%s\n", value);
	if (value)
	{
		value = ft_strdup(value);
		if (!value)
			return (NULL);
		return (value);
	}
	else
		return (NULL);
}

// to reworks (leaks)
static t_envp	*set_new_envp_export(char *envp_line)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	memset(new_envp, 0, sizeof(t_envp));
	new_envp->line = ft_strdup(envp_line);
	if (!new_envp->line)
		return (NULL);
	new_envp->name = set_name_export(envp_line);
	if (!new_envp->name)
		return (NULL);
	new_envp->value = set_value_export(envp_line);
	if (!new_envp->value)
		return (NULL);
	return (new_envp);
}

void	my_export(t_minishell *minishell)
{
	t_envp	*new_envp;
	t_envp	*existing;
	int		i;

	i = 1;
	if (!minishell->cmds->args[1])
		return (print_sorted_envp(minishell));
	if (!minishell->envp)
	{
		minishell->pids[minishell->i] = -2;
		return ;
	}
	while (minishell->cmds->args[i])
	{
		new_envp = set_new_envp_export(minishell->cmds->args[i++]);
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
