/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:23:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 19:58:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>

void	handle_error(t_file *error, t_minishell *minishell)
{
	if (error)
	{
		print_error_file(error);
		minishell->last_status = 1;
	}
	else
		minishell->last_status = 0;
}

void	create_append_files(t_file *append_file, t_minishell *minishell)
{
	append_file->fd = open(append_file->path, O_CREAT | O_WRONLY | O_APPEND,
			0600);
	if (append_file->fd > 0)
		close(append_file->fd);
	else
		exit_perror(minishell, "open");
}

void	create_output(t_file *output, t_minishell *minishell)
{
	output->fd = open(output->path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (output->fd > 0)
		close(output->fd);
	else
		exit_perror(minishell, "open");
}

void	create_files(t_minishell *minishell)
{
	t_file	*redirects;

	redirects = minishell->cmds->redirects;
	while (redirects && redirects != minishell->cmds->error)
	{
		if (redirects->type == append_file)
			create_append_files(redirects, minishell);
		if (redirects->type == output)
			create_output(redirects, minishell);
		redirects = redirects->next;
	}
	handle_error(redirects, minishell);
}
