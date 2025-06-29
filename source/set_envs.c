/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:57:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 19:11:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	**get_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_split(ft_strchr(envp[i], '/'), ':'));
	return (NULL);
}

void	set_envs(t_minishell *minishell, char **envp)
{
	char	**env;
	char	*tmp;
	int		i;

	i = -1;
	env = get_env(envp);
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
	minishell->envp = envp;
}
