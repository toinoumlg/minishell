/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 17:11:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

void	free_and_set_to_next_commands(t_cmd **cmds)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *cmds;
	next = tmp->next;
	tmp->next = NULL;
	free_cmds(tmp);
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
	minishell->paths = NULL;
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
	if (minishell->paths)
		free_array(minishell->paths);
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
	return (minishell->last_status);
}

void	check_for_open_fds(t_minishell *minishell)
{
	int		i;
	t_cmd	*cmds;
	t_file	*files;

	if (minishell->pipe_fds)
	{
		i = 0;
		while (i < minishell->size - 1)
		{
			ft_close(&minishell->pipe_fds[i][0]);
			ft_close(&minishell->pipe_fds[i][1]);
			i++;
		}
	}
	cmds = minishell->cmds;
	while (cmds)
	{
		files = cmds->redirects;
		while (files)
		{
			ft_close(&files->fd);
			files = files->next;
		}
		cmds = cmds->next;
	}
}

void	exit_perror(t_minishell *minishell, char *str)
{
	perror(str);
	check_for_open_fds(minishell);
	exit(free_minishell(minishell));
}
