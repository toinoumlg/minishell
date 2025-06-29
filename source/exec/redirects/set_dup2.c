/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:17:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "pipes.h"
#include "set_dup2_utils.h"

static void	set_files(t_pipex *pipex)
{
	t_file	*redirects;

	redirects = pipex->cmds->redirects;
	while (redirects && redirects != pipex->cmds->error)
	{
		if (redirects->type == input && !is_type_in_redirects(redirects->next,
				here_doc) && dup2_infile(redirects))
			exit_set_files_in_child(pipex);
		if (redirects->type == output && dup2_outfile(redirects))
			exit_set_files_in_child(pipex);
		if (redirects->type == append_file && dup2_append_file(redirects))
			exit_set_files_in_child(pipex);
		redirects = redirects->next;
	}
}

void	set_dup2(t_pipex *pipex)
{
	if (is_type_in_redirects(pipex->cmds->redirects, here_doc))
		handle_here_docs(pipex);
	if (pipex->pipe_fds)
		dup2_pipes(pipex->pipe_fds, pipex->size, pipex->i);
	if (pipex->cmds->redirects)
		set_files(pipex);
}
