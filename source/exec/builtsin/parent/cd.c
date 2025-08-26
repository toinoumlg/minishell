/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/26 19:56:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static char	*set_line(char *getenv_line, char *name)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(name, "=");
	line = ft_strjoin(tmp, getenv_line);
	free(tmp);
	return (line);
}


void	update_pwd(t_envp *envp)
{
	t_envp	*oldpwd;
	t_envp	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	while (envp)
	{
		// fix case where we have unset OLDPWD / PWD
		if (!ft_strncmp("OLDPWD", envp->name, 7))
			oldpwd = envp;
		if (!ft_strncmp("PWD", envp->name, 4))
			pwd = envp;
		envp = envp->next;
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
	{
		perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
		pwd->value = ft_strjoin(oldpwd->value, "/..");
	}
	free(oldpwd->line);
	free(pwd->line);
	pwd->line = set_line(pwd->value, pwd->name);
	oldpwd->line = set_line(oldpwd->value, oldpwd->name);
}

char	*get_env_value(char *name, t_envp *envp)
{
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	cd_error(char *str, int *status)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	*status = -2;
}

void	cd_home(t_minishell *minishell)
{
	char	*home_path;

	home_path = get_env_value("HOME", minishell->envp);
	if (home_path)
	{
		chdir(home_path);
		update_pwd(minishell->envp);
		minishell->pids[minishell->i] = -1;
	}
	else
		cd_error("HOME not set\n", &minishell->pids[minishell->i]);
}

void	cd(t_minishell *minishell)
{
	char	*path;

	path = minishell->cmds->args[1];
	if (!path)
		return (cd_home(minishell));
	if (minishell->cmds->args[2])
		return (cd_error("too many arguments\n",
				&minishell->pids[minishell->i]));
	if (!chdir(path))
	{
		minishell->pids[minishell->i] = -1;
		update_pwd(minishell->envp);
		return ;
	}
	return (cd_error(path, &minishell->pids[minishell->i]), ft_putstr_fd(": ",
			1), perror(""));
}
