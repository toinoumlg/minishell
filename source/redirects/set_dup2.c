/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:50:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 07:20:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

static void	set_files(t_minishell *minishell)
{
	t_file	*redirects;

	redirects = minishell->cmds->redirects;
	while (redirects && redirects != minishell->cmds->error)
	{
		if (redirects->type == input)
			dup2_infile(redirects, minishell);
		if (redirects->type == here_doc_quote
			|| redirects->type == here_doc_word)
			dup2_here_doc(redirects, minishell);
		if (redirects->type == output)
			dup2_outfile(redirects, minishell);
		if (redirects->type == append_file)
			dup2_append_file(redirects, minishell);
		redirects = redirects->next;
	}
}

void	set_dup2(t_minishell *minishell)
{
	if (minishell->pipe_fds)
		dup2_pipes(minishell->pipe_fds, minishell->size, minishell->i,
			minishell);
	if (minishell->cmds->redirects)
		set_files(minishell);
}
