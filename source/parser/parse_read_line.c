/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 15:04:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "alloc.h"
#include "commands.h"
#include "free.h"
#include "parse_error.h"
#include "token.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	free_get_token_list(char *read_line, t_token *tokens,
		char *parse_error)
{
	print_parse_error(parse_error);
	free_tokens(tokens);
	free(read_line);
}

static void	free_set_commands(char *read_line, t_token *tokens, t_cmd *cmds)
{
	free_tokens(tokens);
	free_cmds(cmds);
	free(read_line);
}

void	parse_read_line(char *read_line, t_pipex *pipex, char **env)
{
	t_token	*tokens;
	char	*parse_error;

	parse_error = read_line;
	memset(pipex, 0, sizeof(t_pipex));
	memset(&tokens, 0, sizeof(t_token *));
	if (get_tokens_list(&parse_error, &tokens))
		return (free_get_token_list(read_line, tokens, parse_error));
	if (!tokens)
		return (free(read_line));
	if (set_commands(&tokens, &pipex->cmds))
		return (free_set_commands(read_line, tokens, pipex->cmds));
	try_access(pipex->cmds, env);
	pipex->size = set_size(pipex->cmds);
	pipex->pipe_fds = alloc_pipe_fds(pipex->cmds, pipex->size);
	pipex->pids = alloc_pids(pipex->size);
	add_history(read_line);
	free(read_line);
}
