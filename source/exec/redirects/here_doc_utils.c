/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:05:05 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:17:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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

static int	is_type_in_redirects(t_file *redirects, t_enum_token type)
{
	if (!redirects)
		return (0);
	while (redirects)
	{
		if (redirects->type == type)
			return (1);
		redirects = redirects->next;
	}
	return (0);
}

void	close_here_doc(int here_doc_pipe[2], t_file *here_doc_file,
		t_pipex *pipex)
{
	if (is_type_in_redirects(here_doc_file->next, here_doc))
	{
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
		return ;
	}
	if (!pipex->pipe_fds)
	{
		if (dup2(here_doc_pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
	}
	else
	{
		set_pipe_here_doc(pipex, here_doc_pipe);
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
	}
}
