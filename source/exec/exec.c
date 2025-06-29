/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 19:25:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin_child.h"
#include "builtsin_parent.h"
#include "exec_utils.h"
#include "free.h"
#include "pipes.h"
#include "print_error.h"
#include "set_dup2.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_child_no_execve(t_pipex *pipex)
{
	int		exit_value;
	t_cmd	*cmd;

	cmd = pipex->cmds;
	exit_value = print_command_error(cmd->program, cmd->error);
	print_error_file(cmd->error);
	free_child(pipex);
	exit(exit_value);
}

void	child_process(t_pipex *pipex)
{
	t_cmd	*cmd;

	cmd = pipex->cmds;
	set_dup2(pipex);
	if (!cmd->error)
	{
		exec_builtin_in_child(pipex);
		execve(cmd->program->path, cmd->args, pipex->envp);
	}
	exit_child_no_execve(pipex);
}

void	exec_in_child(t_pipex *pipex)
{
	int	i;

	i = pipex->i;
	pipex->pids[i] = fork();
	if (pipex->pids[i] == -1)
		exit(printf("fork error\n"));
	else if (!pipex->pids[i])
		child_process(pipex);
}

void	try_exec(t_pipex *pipex)
{
	if (is_builtin_to_exec_in_parent(pipex->cmds->args[0]))
		exec_builtin_in_parent(pipex);
	else
		exec_in_child(pipex);
}

void	exec(t_pipex *pipex, char **envp, char **env)
{
	pipex->env = env;
	pipex->envp = envp;
	while (pipex->cmds)
	{
		do_pipe(pipex);
		try_exec(pipex);
		close_pipes(pipex->pipe_fds, pipex->size, pipex->i);
		free_and_set_to_next_commands(&pipex->cmds);
		pipex->i++;
	}
	free(pipex->pipe_fds);
}
