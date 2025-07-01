/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 18:18:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "alloc.h"
#include "commands.h"
#include "free.h"
#include "free_utils.h"
#include "libft.h"
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

static int	get_envp_size(t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}

static char	**set_path_envp(t_envp *envp)
{
	char	**envp_array;
	int		i;

	i = 0;
	envp_array = malloc(sizeof(char *) * (get_envp_size(envp) + 1));
	if (!envp)
		return (NULL);
	while (envp)
	{
		envp_array[i] = ft_strdup(envp->line);
		if (!envp_array[i++])
			return (free_array(envp_array), NULL);
		envp = envp->next;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

void	parse_read_line(char *read_line, t_pipex *pipex, t_minishell *minishell)
{
	t_token	*tokens;
	char	*parse_error;

	parse_error = read_line;
	add_history(read_line);
	memset(pipex, 0, sizeof(t_pipex));
	memset(&tokens, 0, sizeof(t_token *));
	pipex->envp_array = set_path_envp(minishell->envp);
	pipex->envp = &minishell->envp;
	pipex->env = minishell->env;
	if (get_tokens_list(&parse_error, &tokens))
		return (free_get_token_list(read_line, tokens, parse_error));
	if (!tokens)
		return (free(read_line));
	if (set_commands(&tokens, &pipex->cmds))
		return (free_set_commands(read_line, tokens, pipex->cmds));
	try_access(pipex->cmds, minishell->env);
	pipex->size = set_size(pipex->cmds);
	pipex->pipe_fds = alloc_pipe_fds(pipex->cmds, pipex->size);
	pipex->pids = alloc_pids(pipex->size);
	free(read_line);
}
