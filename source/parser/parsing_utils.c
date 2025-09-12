/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:40:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/12 09:47:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "free.h"

int	get_envp_size(t_envp *envp)
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

char	**get_env(char *full_path)
{
	char	**env;
	char	*path;

	path = ft_strchr(full_path, '/');
	if (!path)
		return (NULL);
	env = ft_split(path, ':');
	return (env);
}

void	dup_envp_array(t_minishell *minishell)
{
	t_envp	*envp;
	int		i;

	envp = minishell->envp;
	i = 0;
	while (envp)
	{
		minishell->envp_array[i] = ft_strdup(envp->line);
		if (!minishell->envp_array[i++])
			exit_perror(minishell, "malloc ");
		envp = envp->next;
	}
	minishell->envp_array[i] = NULL;
}

void	dup_env_array(t_minishell *minishell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (minishell->env[i])
	{
		tmp = minishell->env[i];
		minishell->env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!minishell->env[i])
			exit_perror(minishell, "malloc ");
		i++;
	}
	minishell->env[i] = NULL;
}
