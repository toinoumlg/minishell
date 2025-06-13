/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 16:52:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "commands.h"
#include "free.h"
#include "token.h"
#include <stdlib.h>

void	*set_pipe_fds(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (!cmds->next)
		return (NULL);
	while (cmds->next)
	{
		i++;
		cmds = cmds->next;
	}
	return (malloc(sizeof(int[2]) * i));
}

void	*set_pids(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (malloc(sizeof(int) * i));
}

int	set_size(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	parse_read_line(char *read_line, t_minishell *minishell, char **env)
{
	t_token	*tokens;

	if (get_tokens_list(read_line, &tokens))
		return (free_get_token_list(read_line, tokens));
	// expand_tokens();
	if (set_commands(&tokens, &minishell->cmds))
		return (free_set_commands(read_line, tokens, minishell->cmds));
	try_access(minishell->cmds, env);
	minishell->pipe_fds = set_pipe_fds(minishell->cmds);
	minishell->pids = set_pids(minishell->cmds);
	minishell->size = set_size(minishell->cmds);
	free(read_line);
}
