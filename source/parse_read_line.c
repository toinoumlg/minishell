/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 18:29:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "commands.h"
#include "free.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>

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

void	parse_read_line(char *read_line, t_pipex *pipex, char **env)
{
	t_token	*tokens;

	memset(pipex, 0, sizeof(t_minishell));
	if (get_tokens_list(read_line, &tokens))
		return (free_get_token_list(read_line, tokens));
	if (!tokens)
		return ;
	// expand_tokens();
	if (set_commands(&tokens, &pipex->cmds))
		return (free_set_commands(read_line, tokens, pipex->cmds));
	try_access(pipex->cmds, env);
	pipex->pipe_fds = set_pipe_fds(pipex->cmds);
	pipex->pids = set_pids(pipex->cmds);
	pipex->size = set_size(pipex->cmds);
	free(read_line);
}
