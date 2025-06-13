/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 17:07:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parse_read_line.h"
#include "set_env.h"
#include "utils.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

void	dup2_infile(t_cmd *cmd)
{
	cmd->infile->fd = open(cmd->infile->path, O_RDONLY);
	if (cmd->infile->fd > 0)
	{
		if (dup2(cmd->infile->fd, STDIN_FILENO))
			perror("dup2 error:");
		close(cmd->infile->fd);
	}
}

void	set_file_fds(t_minishell *minishell)
{
	if (minishell->cmds->infile && !minishell->cmds->infile->read)
		dup2_infile(minishell->cmds);
	else if (!minishell->cmds->infile && minishell->i > 0
		&& minishell->pipe_fds)
	{
		if (dup2(minishell->pipe_fds[minishell->i - 1][0], STDIN_FILENO) == -1)
			perror("dup2 error:");
		close(minishell->pipe_fds[minishell->i - 1][0]);
	}
	if (minishell->cmds->outfile && (minishell->cmds->outfile->exist
			|| !minishell->cmds->outfile->write))
	{
		minishell->cmds->outfile->fd = open(minishell->cmds->outfile->path,
				O_CREAT | O_WRONLY);
		if (minishell->cmds->outfile->fd > 0)
		{
			if (dup2(minishell->cmds->outfile->fd, STDOUT_FILENO) == -1)
				perror("dup2 error:");
			close(minishell->cmds->outfile->fd);
		}
	}
	else if (!minishell->cmds->outfile && minishell->i < minishell->size - 1
		&& minishell->pipe_fds)
	{
		if (dup2(minishell->pipe_fds[minishell->i][1], STDOUT_FILENO) == -1)
			perror("dup2 error:");
		close(minishell->pipe_fds[minishell->i][1]);
	}
}

void	set_pipes(t_minishell *minishell)
{
	(void)minishell;
}

void	child_process(t_minishell *minishell, char **envp)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	set_file_fds(minishell);
	set_pipes(minishell);
	execve(cmd->program_path, cmd->args, envp);
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
		// print_commands(minishell->cmds);
		free_and_set_to_next_commands(&minishell->cmds);
	}
}

int	is_exit(t_cmd *cmds)
{
	if (cmds && cmds->args && !ft_strncmp(cmds->args[0], "exit", 4))
		return (printf("exit\n"), free_cmds(cmds), 1);
	else
		return (0);
}

void	wait_for_childrens(int *pids, int size)
{
	int	i;
	int	status;

	i = 0;
	while (i < size)
		waitpid(pids[i++], &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*read_line;
	char		**env;
	t_minishell	minishell;

	memset(&minishell, 0, sizeof(t_minishell));
	env = set_env(envp);
	if (!env)
		return (1);
	while (argc && argv)
	{
		read_line = readline("minishell >> ");
		parse_read_line(read_line, &minishell, env);
		if (is_exit(minishell.cmds))
			return (0);
		exec(&minishell, envp);
		wait_for_childrens(minishell.pids, minishell.size);
		memset(&minishell, 0, sizeof(t_minishell));
	}
	return (0);
}
