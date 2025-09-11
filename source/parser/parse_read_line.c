/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 08:11:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "alloc.h"
#include "commands.h"
#include "envp_utils.h"
#include "free.h"
#include "free_utils.h"
#include "libft.h"
#include "parse_error.h"
#include "token.h"
#include "token_expand.h"
#include "utils.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char	**get_env(char *path)
{
	return (ft_split(ft_strchr(path, '/'), ':'));
}

void	set_envp_array(t_minishell *minishell)
{
	int		i;
	t_envp	*envp;

	if (minishell->envp_array)
		free_array(minishell->envp_array);
	envp = minishell->envp;
	i = 0;
	minishell->envp_array = malloc(sizeof(char *) * (get_envp_size(envp) + 1));
	if (!envp)
		exit_perror(minishell, "malloc :");
	while (envp)
	{
		minishell->envp_array[i] = ft_strdup(envp->line);
		if (!minishell->envp_array[i])
			exit_perror(minishell, "malloc :");
		i++;
		envp = envp->next;
	}
	minishell->envp_array[i] = NULL;
}

void	set_env_array(t_minishell *minishell)
{
	char	*tmp;
	int		i;
	t_envp	*path;

	i = 0;
	path = find_existing_envp("PATH", minishell->envp);
	if (minishell->env)
		free_array(minishell->env);
	if (!path)
	{
		minishell->env = NULL;
		return ;
	}
	minishell->env = get_env(path->value);
	if (!minishell->env)
		exit_perror(minishell, "malloc :");
	while (minishell->env[i])
	{
		tmp = minishell->env[i];
		minishell->env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!minishell->env[i])
			exit_perror(minishell, "malloc :");
		i++;
	}
	minishell->env[i] = 0;
}

void	pre_parsing(t_minishell *minishell)
{
	minishell->i = 0;
	set_env_array(minishell);
	set_envp_array(minishell);
}

void	post_parsing(t_minishell *minishell)
{
	try_access(minishell->cmds, minishell->env);
	minishell->size = set_size(minishell->cmds);
	minishell->pipe_fds = alloc_pipe_fds(minishell);
	minishell->pids = alloc_pids(minishell);
}

int	need_merge(t_token *cur, t_token *next)
{
	return (!next->separated_by_space && (cur->type == word
			|| cur->type == simple_quote || cur->type == double_quote)
		&& (next->type == word || next->type == simple_quote
			|| next->type == double_quote));
}

void	merge_adjacent_words(t_token **tokens)
{
	t_token	*cur;
	t_token	*next;
	char	*merged;

	cur = *tokens;
	while (cur && cur->next)
	{
		next = cur->next;
		if (need_merge(cur, next))
		{
			merged = ft_strjoin(cur->string, next->string);
			free(cur->string);
			cur->string = merged;
			cur->next = next->next;
			free(next->string);
			free(next);
		}
		else
			cur = cur->next;
	}
}

void	parse_read_line(t_minishell *minishell)
{
	char	*parse_error;

	if (!minishell->read_line)
	{
		free_minishell(minishell);
		write(2, "exit\n", 5);
		exit(0);
	}
	parse_error = minishell->read_line;
	add_history(minishell->read_line);
	pre_parsing(minishell);
	if (get_tokens_list(&parse_error, minishell))
		return (parsing_error(parse_error, minishell));
	if (!minishell->tokens)
		return (minishell->cmds = NULL, ft_free(minishell->read_line));
	merge_adjacent_words(&minishell->tokens);
	expand_tokens(minishell);
	set_commands(minishell);
	post_parsing(minishell);
}
