/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:26:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/30 12:32:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"

void	dup_std_copy(t_minishell *minishell)
{
	minishell->std_copy[0] = dup(STDIN_FILENO);
	if (minishell->std_copy[0] == -1)
		exit_perror(minishell, "dup");
	minishell->std_copy[1] = dup(STDOUT_FILENO);
	if (minishell->std_copy[1] == -1)
		exit_perror(minishell, "dup");
}

void	dup2_std_copy(t_minishell *minishell)
{
	if (minishell->std_copy[0] >= 0)
	{
		if (dup2(minishell->std_copy[0], STDIN_FILENO) == -1)
			exit_perror(minishell, "dup2");
		close(minishell->std_copy[0]);
	}
	if (minishell->std_copy[1] >= 0)
	{
		if (dup2(minishell->std_copy[1], STDOUT_FILENO) == -1)
			exit_perror(minishell, "dup2");
		close(minishell->std_copy[1]);
	}
}

void	close_all_pipes(t_minishell *minishell)
{
	int	i;

	if (minishell->pipe_fds)
	{
		i = 0;
		while (i < minishell->size - 1)
		{
			ft_close(&minishell->pipe_fds[i][0]);
			ft_close(&minishell->pipe_fds[i][1]);
			i++;
		}
	}
}

void	close_open_fds(t_minishell *minishell)
{
	t_cmd	*cmds;
	t_file	*files;

	ft_close(&minishell->std_copy[0]);
	ft_close(&minishell->std_copy[1]);
	close_all_pipes(minishell);
	cmds = minishell->cmds;
	while (cmds)
	{
		files = cmds->redirects;
		while (files)
		{
			ft_close(&files->fd);
			files = files->next;
		}
		cmds = cmds->next;
	}
}
