/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 19:41:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_utils.h"
#include "minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_cmd(cmds);
		cmds = next;
	}
}

void	free_and_set_to_next_commands(t_cmd **cmds)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *cmds;
	next = tmp->next;
	free_cmd(tmp);
	*cmds = next;
}

void	free_envp(t_envp *envp)
{
	t_envp	*next;

	while (envp)
	{
		next = envp->next;
		if (envp->line)
			ft_free(envp->line);
		if (envp->name)
			ft_free(envp->name);
		if (envp->value)
			ft_free(envp->value);
		ft_free(envp);
		envp = next;
	}
}

int	free_on_exit_error(t_minishell *minishell)
{
	if (minishell->cmds)
		free_cmds(minishell->cmds);
	if (minishell->env)
		free_array(minishell->env);
	if (minishell->envp)
		free_envp(minishell->envp);
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	if (minishell->pids)
		ft_free(minishell->pids);
	if (minishell->pipe_fds)
		ft_free(minishell->pipe_fds);
	if (minishell->read_line)
		ft_free(minishell->read_line);
	if (minishell->tokens)
		free_tokens(minishell->tokens);
	clear_history();
	return (1);
}
