/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 13:48:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "init_envp.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

static char	*set_line_cd(char *getenv_line, char *name)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(name, "=");
	line = ft_strjoin(tmp, getenv_line);
	free(tmp);
	return (line);
}

static char	*set_name_cd(char *envp_line)
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

static char	*set_value_cd(char *envp_line)
{
	char	*value;

	value = ft_strchr(envp_line, '=');
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
static t_envp	*new_envp(char *envp_line)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	memset(new_envp, 0, sizeof(t_envp));
	new_envp->line = ft_strdup(envp_line);
	if (!new_envp->line)
		return (NULL);
	new_envp->name = set_name_cd(envp_line);
	if (!new_envp->name)
		return (NULL);
	new_envp->value = set_value_cd(envp_line);
	if (!new_envp->value)
		return (NULL);
	return (new_envp);
}

// Might need to change and set it to something else than null
t_envp	*add_pwd(t_envp **envp)
{
	t_envp	*pwd;
	char	*line;

	line = "PWD=null";
	pwd = new_envp(line);
	append_new_envp(envp, pwd);
	return (pwd);
}

t_envp	*add_oldpwd(t_envp **envp)
{
	t_envp	*oldpwd;
	char	*line;

	line = "OLDPWD=null";
	oldpwd = new_envp(line);
	append_new_envp(envp, oldpwd);
	return (oldpwd);
}

void	update_pwd(t_envp *envp)
{
	t_envp	*oldpwd;
	t_envp	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	while (envp)
	{
		if (!ft_strncmp("OLDPWD", envp->name, 7))
			oldpwd = envp;
		if (!ft_strncmp("PWD", envp->name, 4))
			pwd = envp;
		envp = envp->next;
	}
	if (!pwd)
		pwd = add_pwd(&envp);
	if (!oldpwd)
		oldpwd = add_oldpwd(&envp);
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
	pwd->line = set_line_cd(pwd->value, pwd->name);
	oldpwd->line = set_line_cd(oldpwd->value, oldpwd->name);
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
	*status = 1;
}

void	cd_home(t_minishell *minishell, int *status)
{
	char	*home_path;

	home_path = get_env_value("HOME", minishell->envp);
	if (home_path)
	{
		chdir(home_path);
		update_pwd(minishell->envp);
		*status = 0;
	}
	else
		cd_error("HOME not set\n", status);
}

void	cd(t_minishell *minishell)
{
	char	*path;
	int		status;

	path = minishell->cmds->args[1];
	if (!path)
		cd_home(minishell, &status);
	else if (minishell->cmds->args[2])
		cd_error("too many arguments\n", &status);
	else if (!chdir(path))
	{
		status = 0;
		update_pwd(minishell->envp);
	}
	else
		cd_error(path, &status), ft_putstr_fd(": ", 2), perror("");
	if (minishell->size > 1)
	{
		free_minishell(minishell);
		exit(status);
	}
	minishell->last_status = status;
}
