/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:57:54 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:11:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_utils.h"
#include "libft.h"
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

char	**set_env(char **envp)
{
	char	**env;
	char	*tmp;
	int		i;

	i = -1;
	env = get_env(envp);
	if (!env)
		return (NULL);
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_array(env), NULL);
		free(env[i]);
		env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!env[i])
			return (free_array(env), NULL);
	}
	return (env);
}
