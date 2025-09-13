/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:02:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/13 12:56:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "free_utils.h"
#include "libft.h"
#include "minishell.h"
#include "parsing_utils.h"
#include <stdio.h>
#include <stdlib.h>

void	set_envp_array(t_minishell *minishell)
{
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	minishell->envp_array = malloc(sizeof(char *)
			* (get_envp_size(minishell->envp) + 1));
	if (!minishell->envp_array)
		exit_perror(minishell, "malloc ");
	dup_envp_array(minishell);
}

void	set_env_array(t_minishell *minishell)
{
	t_envp	*path;

	if (minishell->env)
		free_array(minishell->env);
	path = find_existing_envp("PATH", minishell->envp);
	if (!path)
	{
		minishell->env = NULL;
		return ;
	}
	minishell->env = get_env(path->value);
	if (!minishell->env)
		exit_perror(minishell, "malloc ");
	dup_env_array(minishell);
}
