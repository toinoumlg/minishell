/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 13:37:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipes.h"
#include "token_list.h"
#include <readline/readline.h>
#include <wait.h>

static void	write_in_child(t_pipex *pipex, int here_doc_pipe[2])
{
	char	*read_line;

	while (1)
	{
		read_line = readline(">");
		if (!ft_strncmp(read_line, pipex->cmds->infile->path,
				ft_strlen(pipex->cmds->infile->path)))
		{
			free(read_line);
			close(here_doc_pipe[1]);
			close(here_doc_pipe[0]);
			exit(0);
		}
		write(here_doc_pipe[1], read_line, ft_strlen(read_line));
		write(here_doc_pipe[1], "\n", 1);
		free(read_line);
	}
}

static void	set_here_doc_no_pipe(t_pipex *pipex)
{
	int	here_doc_pipe[2];
	int	pid;

	if (pipe(here_doc_pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		write_in_child(pipex, here_doc_pipe);
	else
	{
		waitpid(pid, NULL, 0);
		close(here_doc_pipe[1]);
		if (dup2(here_doc_pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(here_doc_pipe[0]);
	}
}

static void	dup2_pipes_here_doc(int (*pipe_fds)[2], int size, int i)
{
	if (i == 0)
	{
		if (dup2(pipe_fds[i][0], STDIN_FILENO) == -1)
			perror("dup2 error:");
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			perror("dup2 error:");
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
	}
	else if (i == size - 1)
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2 error:");
		close(pipe_fds[i - 1][0]);
	}
	else
	{
		close(pipe_fds[i][0]);
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2 error:");
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			perror("dup2 error:");
		close(pipe_fds[i][1]);
		close(pipe_fds[i - 1][0]);
	}
}

static void	set_here_doc_with_pipes(t_pipex *pipex)
{
	int	pid;
	int	*here_doc_pipe;

	if (pipex->i < pipex->size - 1)
		here_doc_pipe = pipex->pipe_fds[pipex->i];
	else
		here_doc_pipe = pipex->pipe_fds[pipex->i - 1];
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		write_in_child(pipex, here_doc_pipe);
	else
	{
		waitpid(pid, NULL, 0);
		dup2_pipes_here_doc(pipex->pipe_fds, pipex->size, pipex->i);
	}
}

void	set_here_doc(t_pipex *pipex)
{
	if (!pipex->pipe_fds)
		set_here_doc_no_pipe(pipex);
	else
		set_here_doc_with_pipes(pipex);
}
