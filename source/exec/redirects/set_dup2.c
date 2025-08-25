/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/25 17:45:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "pipes.h"
#include "set_dup2_utils.h"
#include <fcntl.h>
#include <unistd.h>

int	dup2_here_doc(t_file *redirect)
{
	if (dup2(redirect->fd, STDIN_FILENO))
		return (1);
	close(redirect->fd);
	return (0);
}

static void	set_files(t_minishell *minishell)
{
	t_file	*redirects;

	redirects = minishell->cmds->redirects;
	while (redirects && redirects != minishell->cmds->error)
	{
		if (redirects->type == input && dup2_infile(redirects))
			exit_set_files_in_child(minishell);
		if (redirects->type == here_doc && dup2_here_doc(redirects))
			exit_set_files_in_child(minishell);
		if (redirects->type == output && dup2_outfile(redirects))
			exit_set_files_in_child(minishell);
		if (redirects->type == append_file && dup2_append_file(redirects))
			exit_set_files_in_child(minishell);
		redirects = redirects->next;
	}
}

void	set_dup2(t_minishell *minishell)
{
	if (minishell->pipe_fds)
		dup2_pipes(minishell->pipe_fds, minishell->size, minishell->i);
	if (minishell->cmds->redirects)
		set_files(minishell);
}
