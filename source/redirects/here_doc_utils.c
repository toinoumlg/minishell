/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:05:05 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:10:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	set_pipe_here_doc(t_minishell *minishell, int here_doc_pipe[2])
{
	if (minishell->i < minishell->size - 1)
	{
		if (dup2(here_doc_pipe[0], minishell->pipe_fds[minishell->i][0]) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(here_doc_pipe[0], minishell->pipe_fds[minishell->i - 1][0]) ==
			-1)
			perror("dup2");
	}
	if (minishell->i == 0)
		if (dup2(minishell->pipe_fds[minishell->i][0], STDIN_FILENO) == -1)
			perror("dup2");
}

static int	contains_type(t_file *redirects, t_enum_token type)
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
		t_minishell *minishell)
{
	if (contains_type(here_doc_file->next, here_doc))
	{
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
		return ;
	}
	if (!minishell->pipe_fds)
	{
		if (dup2(here_doc_pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
	}
	else
	{
		set_pipe_here_doc(minishell, here_doc_pipe);
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
	}
}
