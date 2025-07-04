/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:05:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "pipes.h"
#include "set_dup2_utils.h"

static void	set_files(t_minishell *minishell)
{
	t_file	*redirects;

	redirects = minishell->cmds->redirects;
	while (redirects && redirects != minishell->cmds->error)
	{
		if (redirects->type == input && !contains_type(redirects->next,
				here_doc) && dup2_infile(redirects))
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
	if (contains_type(minishell->cmds->redirects, here_doc))
		handle_here_docs(minishell);
	if (minishell->pipe_fds)
		dup2_pipes(minishell->pipe_fds, minishell->size, minishell->i);
	if (minishell->cmds->redirects)
		set_files(minishell);
}
