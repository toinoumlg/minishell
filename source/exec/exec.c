/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/04 14:48:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "exec_utils.h"
#include "free.h"
#include "libft.h"
#include "pipes.h"
#include "print_error.h"
#include "set_dup2.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_child_no_execve(t_minishell *minishell)
{
	int		exit_value;
	t_cmd	*cmd;

	cmd = minishell->cmds;
	exit_value = print_command_error(cmd->program, cmd->error);
	print_error_file(cmd->error);
	free_on_exit_error(minishell);
	exit(exit_value);
}

void	child_process(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	set_dup2(minishell);
	if (!cmd->error)
	{
		exec_builtsin_in_child(minishell);
		execve(cmd->program->path, cmd->args, minishell->envp_array);
	}
	exit_child_no_execve(minishell);
}

void	exec_in_child(t_minishell *minishell)
{
	int	i;

	i = minishell->i;
	minishell->pids[i] = fork();
	if (minishell->pids[i] == -1)
		exit(free_on_exit_error(minishell));
	else if (!minishell->pids[i])
		child_process(minishell);
}

void	try_exec(t_minishell *minishell)
{
	if (is_builtin_to_exec_in_parent(minishell->cmds->args[0]))
		exec_builtsin_in_parent(minishell);
	else
		exec_in_child(minishell);
}

void	exec(t_minishell *minishell)
{
	while (minishell->cmds)
	{
		do_pipe(minishell);
		try_exec(minishell);
		close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
		free_and_set_to_next_commands(&minishell->cmds);
		minishell->i++;
	}
	free(minishell->pipe_fds);
	minishell->pipe_fds = NULL;
}
