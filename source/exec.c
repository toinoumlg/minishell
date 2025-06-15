/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 10:23:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "set_files_fds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_file_error(t_file *input, t_file *output)
{
	if (input)
	{
		if (input->exist)
		{
			ft_putstr_fd("minishell >> no such file or directory: ", 2);
			ft_putstr_fd(input->path, 2);
			ft_putstr_fd("\n", 2);
		}
		if (!input->exist && input->read)
		{
			ft_putstr_fd("minishell >> permission denied: ", 2);
			ft_putstr_fd(input->path, 2);
			ft_putstr_fd("\n", 2);
		}
		if (input->is_dir)
		{
			ft_putstr_fd("minishell >> is a directory: ", 2);
			ft_putstr_fd(input->path, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	if (output)
	{
		if (output->write)
		{
			ft_putstr_fd("minishell >> permission denied: ", 2);
			ft_putstr_fd(output->path, 2);
			ft_putstr_fd("\n", 2);
		}
		if (output->is_dir)
		{
			ft_putstr_fd("minishell >> is a directory: ", 2);
			ft_putstr_fd(output->path, 2);
			ft_putstr_fd("\n", 2);
		}
	}
}
int	print_command_error(t_file *program, t_file *infile, t_file *outfile)
{
	if ((infile && infile->read) || (outfile && outfile->write))
		return (1);
	if (program->exist)
		return (ft_putstr_fd("minishell >> cmd not found: ", 2),
			ft_putstr_fd(program->path, 2), ft_putstr_fd("\n", 2), 127);
	else
		return (ft_putstr_fd("minishell >> no rights: ", 2),
			ft_putstr_fd(program->path, 2), ft_putstr_fd("\n", 2), 126);
}

void	exit_child_no_execve(t_minishell *minishell)
{
	int		exit_value;
	t_cmd	*cmd;

	cmd = minishell->cmds;
	exit_value = print_command_error(cmd->program, cmd->infile, cmd->outfile);
	print_file_error(minishell->cmds->infile, minishell->cmds->outfile);
	free_failed_execve(minishell);
	exit(exit_value);
}
void	child_process(t_minishell *minishell, char **envp)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	set_file_fds(minishell);
	if ((!cmd->infile || (cmd->infile && !cmd->infile->read)) && (!cmd->outfile
			|| (cmd->outfile && !cmd->outfile->write)))
		execve(cmd->program->path, cmd->args, envp);
	exit_child_no_execve(minishell);
}

void	parent_process(t_minishell *minishell)
{
	if (minishell->pipe_fds)
	{
		if (minishell->i == 0)
			close(minishell->pipe_fds[minishell->i][1]);
		else if (minishell->i > 0 && minishell->i < minishell->size - 1)
		{
			close(minishell->pipe_fds[minishell->i][1]);
			close(minishell->pipe_fds[minishell->i - 1][0]);
		}
		else if (minishell->i == minishell->size)
			close(minishell->pipe_fds[minishell->i - 1][0]);
	}
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
		free_and_set_to_next_commands(&minishell->cmds);
	}
	free(minishell->pipe_fds);
}
