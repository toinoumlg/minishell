/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:02:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 20:01:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	get_envp_size(t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}

static void	join_paths(t_minishell *minishell)
{
	int		i;
	char	*tmp;
	char	*join;

	i = 0;
	while (minishell->paths[i])
	{
		tmp = minishell->paths[i];
		join = ft_strjoin(tmp, "/");
		if (!join)
			exit_perror(minishell, "malloc ");
		minishell->paths[i++] = join;
		free(tmp);
	}
	minishell->paths[i] = NULL;
}

void	set_envp_array(t_minishell *minishell)
{
	t_envp	*envp;
	char	*tmp;
	int		i;

	envp = minishell->envp;
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	minishell->envp_array = malloc(sizeof(char *)
			* (get_envp_size(minishell->envp) + 1));
	if (!minishell->envp_array)
		exit_perror(minishell, "malloc ");
	i = 0;
	while (envp)
	{
		tmp = ft_strdup(envp->line);
		if (!tmp)
			exit_perror(minishell, "malloc ");
		minishell->envp_array[i++] = tmp;
		envp = envp->next;
	}
	minishell->envp_array[i] = NULL;
}

void	set_paths(t_minishell *minishell)
{
	t_envp	*path;

	if (minishell->paths)
		free_array(minishell->paths);
	path = find_existing_envp("PATH", minishell->envp);
	if (path && path->value)
	{
		minishell->paths = ft_split(path->value, ':');
		if (!minishell->paths)
			exit_perror(minishell, "malloc ");
		return (join_paths(minishell));
	}
	minishell->paths = NULL;
}
