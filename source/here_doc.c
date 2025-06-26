/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 17:02:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "pipes.h"
#include "token_list.h"
#include <readline/readline.h>
#include <wait.h>

static void	close_pipes_here_doc(int (*pipe_fds)[2], int i, int size)
{
	if (i == 0)
	{
		close(pipe_fds[i][1]);
		close(pipe_fds[i][0]);
	}
	else if (i == size - 1)
		close(pipe_fds[i - 1][0]);
	else
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		close(pipe_fds[i - 1][0]);
	}
}

static void	write_in_child(t_pipex *pipex, int here_doc_pipe[2])
{
	char	*read_line;

	while (1)
	{
		read_line = readline(">");
		if (!ft_strncmp(read_line, pipex->cmds->here_doc->path,
				ft_strlen(pipex->cmds->here_doc->path)))
		{
			free(read_line);
			close(here_doc_pipe[1]);
			close(here_doc_pipe[0]);
			if (pipex->pipe_fds)
				close_pipes_here_doc(pipex->pipe_fds, pipex->i, pipex->size);
			free_child(pipex);
			exit(0);
		}
		write(here_doc_pipe[1], read_line, ft_strlen(read_line));
		write(here_doc_pipe[1], "\n", 1);
		free(read_line);
	}
}

static void	set_pipe_here_doc(t_pipex *pipex, int here_doc_pipe[2])
{
	if (pipex->i < pipex->size - 1)
	{
		if (dup2(here_doc_pipe[0], pipex->pipe_fds[pipex->i][0]) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(here_doc_pipe[0], pipex->pipe_fds[pipex->i - 1][0]) == -1)
			perror("dup2");
	}
	if (pipex->i == 0)
		if (dup2(pipex->pipe_fds[pipex->i][0], STDIN_FILENO) == -1)
			perror("dup2");
}

void	set_here_doc(t_pipex *pipex)
{
	int	pid;
	int	here_doc_pipe[2];

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
		if (!pipex->pipe_fds)
		{
			if (dup2(here_doc_pipe[0], STDIN_FILENO) == -1)
				perror("dup2");
		}
		else
		{
			set_pipe_here_doc(pipex, here_doc_pipe);
			close(here_doc_pipe[0]);
			close(here_doc_pipe[1]);
		}
	}
}
