/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:58:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 16:37:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	set_name(t_envp *new, t_minishell *minishell)
{
	char	c;
	int		i;

	i = 0;
	while (new->line[i])
	{
		if (new->line[i] == '=')
		{
			new->contains_sign = 1;
			break ;
		}
		i++;
	}
	c = new->line[i];
	new->line[i] = 0;
	new->name = ft_strdup(new->line);
	if (!new->name)
		exit_perror(minishell, "malloc");
	new->line[i] = c;
}

void	set_value(t_envp *new, t_minishell *minishell)
{
	char	*tmp;

	if (new->contains_sign)
	{
		tmp = ft_strchr(new->line, '=');
		if (*(tmp + 1))
		{
			new->value = ft_strdup(tmp + 1);
			if (!new->value)
				exit_perror(minishell, "malloc");
		}
	}
}

void	append_new_envp(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	tmp = *envp;
	if (!tmp)
	{
		*envp = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// t_envp	*set_new_envp(char *envp_line, t_minishell *minishell)
// {
// 	t_envp	*new_envp;

// 	new_envp = malloc(sizeof(t_envp));
// 	if (!new_envp)
// 		exit_perror(minishell, "malloc :");
// 	memset(new_envp, 0, sizeof(t_envp));
// 	new_envp->line = ft_strdup(envp_line);
// 	if (!new_envp->line)
// 		exit_perror(minishell, "malloc :");
// 	set_name(new_envp, minishell);
// 	set_value(new_envp, minishell);
// 	return (new_envp);
// }

/*	Return a pointer to envp struct that match specified name.
	Return NULL if not in environnement.	*/
t_envp	*find_existing_envp(char *name, t_envp *envp)
{
	int	i;

	i = 0;
	if (!envp || !name)
		return (NULL);
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (envp);
		i++;
		envp = envp->next;
	}
	return (NULL);
}
