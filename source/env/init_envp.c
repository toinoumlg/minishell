/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:41:48 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 10:11:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

static void	set_line(t_envp *envp)
{
	char	*tmp;

	free(envp->line);
	tmp = ft_strjoin(envp->name, "=");
	if (!tmp)
		return ;
	envp->line = ft_strjoin(tmp, envp->value);
	free(tmp);
}

/// @brief HORRIBLE A REFAIRE
/// @param minishell
// void	set_basic_envp(t_minishell *minishell)
// {
// 	char	*tmp;
// 	char	*full_line;

// 	tmp = getcwd(NULL, 0);
// 	full_line = ft_strjoin("PWD=", tmp);
// 	append_new_envp(&minishell->envp, set_new_envp(full_line));
// 	free(full_line);
// 	full_line = ft_strjoin("OLDPWD=", tmp);
// 	append_new_envp(&minishell->envp, set_new_envp(full_line));
// 	free(tmp);
// 	free(full_line);
// 	append_new_envp(&minishell->envp, set_new_envp("_"));
// }

void	update_shlvl(t_minishell *minishell)
{
	t_envp	*shlvl;
	int		nb;

	shlvl = find_existing_envp("SHLVL", minishell->envp);
	if (shlvl)
	{
		nb = ft_atoi(shlvl->value);
		nb++;
		free(shlvl->value);
		shlvl->value = ft_itoa(nb);
		if (!shlvl->value)
			exit(free_envp(minishell->envp));
		set_line(shlvl);
	}
}

// Parse all the provided envp array and create a struct containing:
// char *line = full line of the variable
// char *name = left-side of the equal-sign
// char *value = right-side of the equal sign
void	init_envp(t_minishell *minishell, char **envp)
{
	int		i;
	t_envp	*new_envp;

	memset(minishell, 0, sizeof(t_minishell));
	i = 0;
	// if (!envp || !envp[i])
	// 	return (set_basic_envp(minishell));
	while (envp[i])
	{
		new_envp = malloc(sizeof(t_envp));
		if (!new_envp)
			exit_perror(minishell, "malloc :");
		memset(new_envp, 0, sizeof(t_envp));
		append_new_envp(&minishell->envp, new_envp);
		new_envp->line = ft_strdup(envp[i]);
		if (!new_envp->line)
			exit_perror(minishell, "malloc :");
		new_envp->name = set_name(envp[i], minishell);
		if (!new_envp->name)
			exit_perror(minishell, "malloc :");
		new_envp->value = set_value(envp[i++], minishell);
	}
	update_shlvl(minishell);
}
