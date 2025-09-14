/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:18 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 11:43:34 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <stdio.h>

static void	pwd_error(t_minishell *minishell)
{
	char	**args;

	args = minishell->cmds->args;
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("bad option: ", 2);
	ft_putchar_fd(args[1][0], 2);
	ft_putchar_fd(args[1][1], 2);
	ft_putstr_fd("\n", 2);
	free_minishell(minishell);
	exit(1);
}

static char	*get_env_value(char *name, t_envp *envp)
{
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	pwd(t_minishell *minishell)
{
	char	*path;
	int		to_free;

	to_free = 0;
	if (minishell->cmds->args[1] && minishell->cmds->args[1][0] == '-')
		pwd_error(minishell);
	path = get_env_value("PWD", minishell->envp);
	if (!path)
	{
		path = getcwd(NULL, 0);
		if (!path)
			exit_perror(minishell, "minishell: getcwd");
		to_free = 1;
	}
	printf("%s\n", path);
	if (to_free)
		free(path);
	free_minishell(minishell);
	exit(0);
}
