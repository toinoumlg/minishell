/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/14 15:52:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "set_files_fds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	set_file_error(t_file *file)
{
}

int	print_command_error(t_file *program)
{
}

int	set_exit_value(t_file *file)
{
	if (file->exist)
		return (127);
	if (file->exec)
		return (126);
}

void	child_process(t_minishell *minishell, char **envp)
{
	t_cmd	*cmd;
	int		exit;

	cmd = minishell->cmds;
	set_file_fds(minishell);
	execve(cmd->program->path, cmd->args, envp);
	exit = set_exit_value(cmd->program);
	free_failed_execve(minishell);
	exit(1);
}

void	parent_process(t_minishell *minishell)
{
	if (minishell->i == 0 && minishell->pipe_fds)
		close(minishell->pipe_fds[minishell->i][1]);
	else if (minishell->i > 0 && minishell->i < minishell->size - 1)
	{
		close(minishell->pipe_fds[minishell->i][1]);
		close(minishell->pipe_fds[minishell->i - 1][0]);
	}
	else if (minishell->i == minishell->size)
		close(minishell->pipe_fds[minishell->i - 1][0]);
}

void	exec_one(t_minishell *minishell, char **envp)
{
	int	i;

	i = minishell->i;
	if (minishell->cmds->next)
		if (pipe(minishell->pipe_fds[i]) == -1)
			exit(printf("pipe creation error\n"));
	minishell->pids[i] = fork();
	if (minishell->pids[i] == -1)
		exit(printf("fork error\n"));
	else if (minishell->pids[i] == 0)
		child_process(minishell, envp);
	else
		parent_process(minishell);
}

void	exec(t_minishell *minishell, char **envp)
{
	while (minishell->cmds)
	{
		exec_one(minishell, envp);
		minishell->i++;
		set_file_error();
		free_and_set_to_next_commands(&minishell->cmds);
	}
	free(minishell->pipe_fds);
}
