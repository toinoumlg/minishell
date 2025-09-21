/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 15:52:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_utils.h"
#include "minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

t_token	*tail(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

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

int	free_envp(t_envp *envp)
{
	t_envp	*next;

	while (envp)
	{
		next = envp->next;
		if (envp->line)
			free(envp->line);
		if (envp->name)
			free(envp->name);
		if (envp->value)
			free(envp->value);
		free(envp);
		envp = next;
	}
	return (1);
}

void	set_minishell_to_null(t_minishell *minishell)
{
	minishell->cmds = NULL;
	minishell->env = NULL;
	minishell->envp = NULL;
	minishell->envp_array = NULL;
	minishell->read_line = NULL;
	minishell->pids = NULL;
	minishell->pipe_fds = NULL;
	minishell->tokens = NULL;
}

int	free_minishell(t_minishell *minishell)
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
		free(minishell->pids);
	if (minishell->read_line)
		free(minishell->read_line);
	if (minishell->pipe_fds)
		free(minishell->pipe_fds);
	if (minishell->tokens)
		free_tokens(minishell->tokens);
	set_minishell_to_null(minishell);
	clear_history();
	return (minishell->last_status);
}

int	exit_perror(t_minishell *minishell, char *str)
{
	perror(str);
	exit(free_minishell(minishell));
}
