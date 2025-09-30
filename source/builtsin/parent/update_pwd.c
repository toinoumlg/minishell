/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:18:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 15:06:57 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "envp.h"
#include "free.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

static void	update_line(t_envp *new, t_minishell *minishell)
{
	char	*tmp;

	free(new->line);
	if (!new->contains_sign)
	{
		new->line = ft_strdup(new->name);
		if (!new->line)
			exit_perror(minishell, "malloc");
		return ;
	}
	tmp = ft_strjoin(new->name, "=");
	if (new->value)
	{
		new->line = ft_strjoin(tmp, new->value);
		free(tmp);
		if (!new->line)
			exit_perror(minishell, "malloc");
	}
	else
		new->line = tmp;
}

static t_envp	*add_to_envp(char *line, t_minishell *minishell)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		exit_perror(minishell, "malloc");
	ft_memset(new, 0, sizeof(t_envp));
	append_new_envp(&minishell->envp, new);
	new->line = ft_strdup(line);
	if (!new->line)
		exit_perror(minishell, "malloc");
	set_name(new, minishell);
	set_value(new, minishell);
	return (new);
}

static void	handle_getcwd_error(t_envp *oldpwd, t_envp *pwd,
		t_minishell *minishell)
{
	ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
	perror("getcwd: cannot access parent directories");
	if (oldpwd->value)
		pwd->value = ft_strjoin(oldpwd->value, "/..");
	else
		pwd->value = ft_strdup("..");
	if (!pwd->value)
		exit_perror(minishell, "malloc");
}

void	update_pwd(t_minishell *minishell)
{
	t_envp	*oldpwd;
	t_envp	*pwd;

	oldpwd = find_existing_envp(OLDPWD, minishell->envp);
	pwd = find_existing_envp(_PWD, minishell->envp);
	if (!pwd)
		pwd = add_to_envp(_PWD, minishell);
	if (!oldpwd)
		oldpwd = add_to_envp(OLDPWD, minishell);
	if (oldpwd->value)
		free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		handle_getcwd_error(oldpwd, pwd, minishell);
	update_line(pwd, minishell);
	update_line(oldpwd, minishell);
}
