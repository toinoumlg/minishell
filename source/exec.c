/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/23 19:06:04 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_builtsin.h"
#include "free.h"
#include "libft.h"
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

int	is_child_executable(t_cmd *cmd)
{
	return (!cmd->infile || (cmd->infile && !cmd->infile->read))
		&& (!cmd->outfile || (cmd->outfile && !cmd->outfile->write));
}

void	child_process(t_pipex *pipex, char **envp)
{
	t_cmd	*cmd;

	cmd = pipex->cmds;
	set_file_fds(pipex);
	if (is_child_executable(cmd))
	{
		exec_child_builtins(pipex);
		execve(cmd->program->path, cmd->args, envp);
	}
	exit_child_no_execve(pipex);
}

void	exec_one(t_pipex *pipex, char **envp)
{
	int	i;

	i = pipex->i;
	pipex->pids[i] = fork();
	if (pipex->pids[i] == -1)
		exit(printf("fork error\n"));
	else if (pipex->pids[i] == 0)
		child_process(pipex, envp);
}

int	is_builtin_to_exec_in_parent(char *cmd)
{
	return (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "exit", 5));
}

void	my_exit(t_pipex *pipex, char **env)
{
	if (pipex->i != 0)
		return ;
	printf("exit\n");
	close_all_pipes(pipex->pipe_fds, pipex->size, pipex->i);
	free_cmds(pipex->cmds);
	free_array(env);
	if (pipex->pipe_fds)
		free(pipex->pipe_fds);
	if (pipex->pids)
		free(pipex->pids);
	exit(0);
}

void	exec_parent_builtin(t_pipex *pipex, char **env)
{
	int	i;

	i = pipex->i;
	pipex->pids[i] = -1;
	if (!ft_strncmp(pipex->cmds->args[0], "cd", 3))
		cd(pipex->cmds->args[1]);
	if (!ft_strncmp(pipex->cmds->args[0], "exit", 5))
		my_exit(pipex, env);
}

void	exec(t_pipex *pipex, char **envp, char **env)
{
	while (pipex->cmds)
	{
		if (pipex->size > 1 && pipex->i < pipex->size - 1)
			if (pipe(pipex->pipe_fds[pipex->i]) == -1)
				exit(printf("pipe creation error\n"));
		if (pipex->cmds->args
			&& is_builtin_to_exec_in_parent(pipex->cmds->args[0]))
			exec_parent_builtin(pipex, env);
		else
			exec_one(pipex, envp);
		pipex->i++;
		free_and_set_to_next_commands(&pipex->cmds);
	}
	close_all_pipes(pipex->pipe_fds, pipex->size, pipex->i);
	free(pipex->pipe_fds);
}
