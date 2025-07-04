/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_no_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:31:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/04 13:49:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_var.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <string.h>

static char	*set_line(char *getenv_line, char *name)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(name, "=");
	line = ft_strjoin(tmp, getenv_line);
	free(tmp);
	return (line);
}

static t_envp	*set_new_envp(char *getenv_line, char *name)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_envp));
	new->line = set_line(getenv_line, name);
	if (!new->line)
		return (free(new), NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (free(new->line), free(new), NULL);
	new->value = ft_strdup(getenv_line);
	if (!new->value)
		return (free(new->name), free(new->line), free(new), NULL);
	return (new);
}

static void	append_new_envp(t_envp **envp_struct, t_envp *new)
{
	t_envp	*tmp;
	t_envp	*head;

	tmp = *envp_struct;
	head = tmp;
	if (!tmp)
	{
		*envp_struct = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*envp_struct = head;
}

void	set_envp_no_input(t_envp **envp_struct)
{
	t_envp	*new;

	new = set_new_envp(getenv(PATH), PATH);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(USER), USER);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(HOME), HOME);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(DESKTOP_SESSION), DESKTOP_SESSION);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(SHELL), SHELL);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(USERNAME), USERNAME);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(PWD), PWD);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(OLDPWD), OLDPWD);
	append_new_envp(envp_struct, new);
	new = set_new_envp(getenv(TERM), TERM);
	append_new_envp(envp_struct, new);
}
