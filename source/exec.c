/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 18:58:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin_child.h"
#include "builtsin_parent.h"
#include "exec_utils.h"
#include "free.h"
#include "minishell.h"
#include "pipes.h"
#include "print_error.h"
#include "set_files_fds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_child_no_execve(t_pipex *pipex)
{
	int		exit_value;
	t_cmd	*cmd;

	cmd = pipex->cmds;
	exit_value = print_command_error(cmd->program, cmd->infile, cmd->outfile);
	print_error_file(cmd->infile, cmd->outfile);
	free_child(pipex);
	exit(exit_value);
}

void	child_process(t_pipex *pipex, char **envp)
{
	t_cmd	*cmd;

	cmd = pipex->cmds;
	set_file_fds(pipex);
	if (is_child_executable(cmd))
	{
		exec_builtin_in_child(pipex);
		execve(cmd->program->path, cmd->args, envp);
	}
	exit_child_no_execve(pipex);
}

void	exec_in_child(t_pipex *pipex, char **envp)
{
	int	i;

	i = pipex->i;
	pipex->pids[i] = fork();
	if (pipex->pids[i] == -1)
		exit(printf("fork error\n"));
	else if (pipex->pids[i] == 0)
		child_process(pipex, envp);
}

void	try_exec(t_pipex *pipex, char **envp, char **env)
{
	if (is_builtin_to_exec_in_parent(pipex->cmds->args[0]))
		exec_builtin_in_parent(pipex, env);
	else
		exec_in_child(pipex, envp);
}

void	exec(t_pipex *pipex, char **envp, char **env)
{
	while (pipex->cmds)
	{
		do_pipe(pipex);
		try_exec(pipex, envp, env);
		close_pipes(pipex->pipe_fds, pipex->size, pipex->i);
		free_and_set_to_next_commands(&pipex->cmds);
		pipex->i++;
	}
	free(pipex->pipe_fds);
}
