/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:13:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "alloc.h"
#include "commands.h"
#include "free.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	parse_error(void)
{
	printf("Error parsing ...");
}

static void	free_get_token_list(char *read_line, t_token *tokens)
{
	free(read_line);
	free_tokens(tokens);
	parse_error();
}

static void	free_set_commands(char *read_line, t_token *tokens, t_cmd *cmds)
{
	free(read_line);
	free_tokens(tokens);
	free_cmds(cmds);
	parse_error();
}

void	parse_read_line(char *read_line, t_pipex *pipex, char **env)
{
	t_token	*tokens;

	memset(pipex, 0, sizeof(t_pipex));
	memset(&tokens, 0, sizeof(t_token *));
	if (get_tokens_list(read_line, &tokens))
		return (free_get_token_list(read_line, tokens));
	if (!tokens)
		return (free(read_line));
	if (set_commands(&tokens, &pipex->cmds))
		return (free_set_commands(read_line, tokens, pipex->cmds));
	try_access(pipex->cmds, env);
	pipex->size = set_size(pipex->cmds);
	pipex->pipe_fds = alloc_pipe_fds(pipex->cmds, pipex->size);
	pipex->pids = alloc_pids(pipex->size);
	free(read_line);
}
