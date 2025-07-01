/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:57:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 18:40:47 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "envp.h"
#include "free_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	**get_env(char *path)
{
	return (ft_split(ft_strchr(path, '/'), ':'));
}

static int	same_name(char *name, char *envp_name)
{
	return (!(ft_strncmp(name, envp_name, ft_strlen(name) + 1)));
}

static char	*get_envp_line(t_envp *envp, char *name)
{
	while (envp && !same_name(name, envp->name))
		envp = envp->next;
	if (!envp)
		return (NULL);
	return (envp->line);
}

void	set_envs(t_minishell *minishell, char **envp)
{
	char	**env;
	char	*tmp;
	int		i;

	i = -1;
	envp = NULL;
	set_envp(&minishell->envp, envp);
	env = get_env(get_envp_line(minishell->envp, PATH));
	if (!env)
		exit(1);
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_array(env), exit(1));
		free(env[i]);
		env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!env[i])
			return (free_array(env), exit(1));
	}
	minishell->env = env;
}
