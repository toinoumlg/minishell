/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 18:47:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "envp.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

int	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	return (1);
}

int	cd_home(t_minishell *minishell)
{
	t_envp	*home;

	home = find_existing_envp("HOME", minishell->envp);
	if (home)
	{
		if (!chdir(home->value))
			return (update_pwd(minishell), 0);
		else
			return (perror("chdir"), 0);
	}
	else
		return (cd_error("HOME not set\n"), 1);
}

int	cd_oldpwd(t_minishell *minishell)
{
	t_envp	*oldpwd;

	oldpwd = find_existing_envp("OLDPWD", minishell->envp);
	if (oldpwd)
	{
		if (!chdir(oldpwd->value))
			return (printf("%s\n", oldpwd->value), update_pwd(minishell), 0);
		else
			return (perror("chdir"), 1);
	}
	else
		return (cd_error("OLDPWD not set\n"), 1);
}

int	cd_path(t_minishell *minishell)
{
	char	*path;

	path = minishell->cmds->args[1];
	if (!chdir(path))
		return ((update_pwd(minishell), 0));
	else
		return (perror("chdir"), 1);
}

int	cd(t_minishell *minishell)
{
	char	**args;

	args = minishell->cmds->args;
	if (args[1] && args[2])
		return (cd_error("too many arguments\n"));
	if (!args[1] || (args[1][0] == '~' && !args[1][1]))
		return (cd_home(minishell));
	else if (args[1][0] == '-' && !args[1][1])
		return (cd_oldpwd(minishell));
	else
		return (cd_path(minishell));
}
