/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:18:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/23 18:58:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
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

static char	*set_name_cd(char *line)
{
	char	*name;
	int		i;

	i = -1;
	name = ft_strdup(line);
	if (!name)
		return (NULL);
	while (line[++i])
	{
		if (line[i] == '=')
		{
			name[i] = 0;
			return (name);
		}
	}
	return (name);
}

static char	*set_value_cd(char *line)
{
	char	*value;

	value = ft_strchr(line, '=');
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
static t_envp	*new_envp(char *line)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	memset(new_envp, 0, sizeof(t_envp));
	new_envp->line = ft_strdup(line);
	if (!new_envp->line)
		return (NULL);
	new_envp->name = set_name_cd(line);
	if (!new_envp->name)
		return (NULL);
	new_envp->value = set_value_cd(line);
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

// void	update_pwd(t_minishell *minishell, char *new_pwd)
// {
// 	t_envp *oldpwd;
// 	t_envp *pwd;

// 	oldpwd = find_existing_envp("OLDPWD", minishell->envp);
// 	pwd = find_existing_envp("PWD", minishell->envp);

// 	if(oldpwd && pwd)
// 	{

// 	}

// 	free(pwd->value);
// 	pwd->value = getcwd(NULL, 0);
// 	if (!pwd->value)
// 	{
// 		perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
// 		pwd->value = ft_strjoin(oldpwd->value, "/..");
// 	}
// 	free(oldpwd->line);
// 	free(pwd->line);
// 	pwd->line = set_line_cd(pwd->value, pwd->name);
// 	oldpwd->line = set_line_cd(oldpwd->value, oldpwd->name);
// }