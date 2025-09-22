/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:41:48 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 16:52:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

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

/*	Update shell level var in the environnment (add + 1)	*/
void	update_shlvl(t_minishell *minishell)
{
	t_envp	*shlvl;
	int		nb;
	char	*tmp;

	shlvl = find_existing_envp("SHLVL", minishell->envp);
	if (shlvl)
	{
		nb = ft_atoi(shlvl->value);
		nb++;
		free(shlvl->value);
		shlvl->value = ft_itoa(nb);
		if (!shlvl->value)
			exit(free_minishell(minishell));
		free(shlvl->line);
		tmp = ft_strjoin(shlvl->name, "=");
		if (!tmp)
			exit_perror(minishell, "malloc ");
		shlvl->line = ft_strjoin(tmp, shlvl->value);
		free(tmp);
		if (!shlvl->line)
			exit_perror(minishell, "malloc ");
	}
}

/*	Parse all the provided envp array and create a struct containing:
	char *line = full line of the variable
	char *name = left-side of the equal-sign
	char *value = right-side of the equal sign	*/
void	set_envp(t_minishell *minishell, char **envp)
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
			exit_perror(minishell, "malloc ");
		memset(new_envp, 0, sizeof(t_envp));
		append_new_envp(&minishell->envp, new_envp);
		new_envp->line = ft_strdup(envp[i++]);
		if (!new_envp->line)
			exit_perror(minishell, "malloc ");
		set_name(new_envp, minishell);
		set_value(new_envp, minishell);
	}
	update_shlvl(minishell);
}
