/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/16 17:34:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	parse_error(void)
{
	printf("Error parsing ...");
}

void	free_array(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->string)
			free(tokens->string);
		free(tokens);
		tokens = next;
	}
}

void	free_file(t_file *file)
{
	if (file->path)
		free(file->path);
	free(file);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		if (cmds->args)
			free_array(cmds->args);
		if (cmds->program)
			free_file(cmds->program);
		if (cmds->infile)
			free_file(cmds->infile);
		if (cmds->outfile)
			free_file(cmds->outfile);
		free(cmds);
		cmds = next;
	}
}

void	free_get_token_list(char *read_line, t_token *tokens)
{
	free(read_line);
	free_tokens(tokens);
	parse_error();
}

void	free_set_commands(char *read_line, t_token *tokens, t_cmd *cmds)
{
	free(read_line);
	free_tokens(tokens);
	free_cmds(cmds);
	parse_error();
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	if (cmd->program)
		free_file(cmd->program);
	if (cmd->infile)
		free_file(cmd->infile);
	if (cmd->outfile)
		free_file(cmd->outfile);
	free(cmd);
}

void	free_and_set_to_next_commands(t_cmd **cmds)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *cmds;
	next = tmp->next;
	free_cmd(tmp);
	*cmds = next;
}

void	free_child(t_pipex *pipex)
{
	free_cmds(pipex->cmds);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->pipe_fds)
		free(pipex->pipe_fds);
}
