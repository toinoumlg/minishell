/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:12:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "here_doc_utils.h"
#include "libft.h"
#include "token_list.h"
#include <readline/readline.h>
#include <wait.h>

static void	close_pipes_in_write_child(int (*pipe_fds)[2], int i, int size)
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

static void	write_in_child(t_pipex *pipex, int here_doc_pipe[2],
		char *here_doc_lim)
{
	char	*read_line;

	while (1)
	{
		read_line = readline(">");
		if (!ft_strncmp(read_line, here_doc_lim, ft_strlen(here_doc_lim)))
		{
			free(read_line);
			close(here_doc_pipe[1]);
			close(here_doc_pipe[0]);
			if (pipex->pipe_fds)
				close_pipes_in_write_child(pipex->pipe_fds, pipex->i,
					pipex->size);
			free_child(pipex);
			exit(0);
		}
		write(here_doc_pipe[1], read_line, ft_strlen(read_line));
		write(here_doc_pipe[1], "\n", 1);
		free(read_line);
	}
}

void	set_here_doc(t_pipex *pipex, t_file *here_doc_file)
{
	int	pid;
	int	here_doc_pipe[2];

	if (pipe(here_doc_pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		write_in_child(pipex, here_doc_pipe, here_doc_file->path);
	else
	{
		waitpid(pid, NULL, 0);
		close_here_doc(here_doc_pipe, here_doc_file, pipex);
	}
}

void	handle_here_docs(t_pipex *pipex)
{
	t_file	*redirects;

	redirects = pipex->cmds->redirects;
	while (redirects)
	{
		if (redirects->type == here_doc)
			set_here_doc(pipex, redirects);
		redirects = redirects->next;
	}
}
