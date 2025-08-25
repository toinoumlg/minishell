/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/25 19:13:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

	while (envp)
	{
		if (!ft_strncmp("OLDPWD", envp->name, 7))
			oldpwd = envp;
		if (!ft_strncmp("PWD", envp->name, 4))
			pwd = envp;
		envp = envp->next;
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	free(oldpwd->line);
	free(pwd->line);
	pwd->line = set_line(pwd->value, pwd->name);
	oldpwd->line = set_line(oldpwd->value, oldpwd->name);
}

void	cd(t_minishell *minishell)
{
	char	*home_path;
	char	*path;

	path = minishell->cmds->args[1];
	if (!path)
	{
		home_path = getenv("HOME");
		chdir(home_path);
		update_pwd(minishell->envp);
		minishell->pids[minishell->i] = -1;
		return ;
	}
	if (!chdir(path))
	{
		minishell->pids[minishell->i] = -1;
		update_pwd(minishell->envp);
		return ;
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	minishell->pids[minishell->i] = -2;
}
