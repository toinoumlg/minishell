/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 13:26:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "create_files.h"
#include "envp_utils.h"
#include "exec_utils.h"
#include "free.h"
#include "free_utils.h"
#include "libft.h"
#include "pipes.h"
#include "set_dup2.h"
#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	close_here_doc(t_file *redirects)
{
	while (redirects)
	{
		if (redirects->type == here_doc)
			close(redirects->fd);
		redirects = redirects->next;
	}
}

void	child_process(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	set_signals_child();
	set_dup2(minishell);
	if (!cmd->error)
	{
		exec_builtsin_in_child(minishell);
		execve(cmd->program->path, cmd->args, minishell->envp_array);
	}
	exit_child(minishell);
}

void	exec_in_child(t_minishell *minishell)
{
	int	i;

	i = minishell->i;
	minishell->pids[i] = fork();
	if (minishell->pids[i] == -1)
		exit_perror(minishell, "fork");
	else if (!minishell->pids[i])
		child_process(minishell);
}

// if the command have no args but redirect
void	try_exec(t_minishell *minishell)
{
	if (!minishell->cmds->args && minishell->cmds->redirects)
		return (create_files(minishell));
	if (!minishell->cmds->args)
		return ;
	exec_in_child(minishell);
}

void	exec(t_minishell *minishell)
{
	if (!minishell->cmds)
		return ;
	if (is_builtin_to_exec_in_parent(minishell))
		return (exec_builtsin_in_parent(minishell));
	while (minishell->cmds)
	{
		do_pipe(minishell);
		// handle_underscore(minishell);
		try_exec(minishell);
		close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
		close_here_doc(minishell->cmds->redirects);
		free_and_set_to_next_commands(&minishell->cmds);
		minishell->i++;
	}
	if (minishell->pipe_fds)
		free(minishell->pipe_fds);
	minishell->pipe_fds = NULL;
}
