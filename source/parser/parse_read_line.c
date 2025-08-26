/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/26 19:41:59 by amalangu         ###   ########.fr       */
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

static char	**set_envp_array(t_envp *envp)
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

char	**set_env_array(t_minishell *minishell)
{
	char	**env;
	char	*tmp;
	int		i;

	i = -1;
	env = get_env(find_existing_envp("PATH", minishell->envp)->value);
	while (env[++i])
	{
		tmp = env[i];
		env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!env[i])
			return (free_array(env), exit(free_on_exit_error(minishell)), NULL);
	}
	return (env);
}

void	pre_parsing(t_minishell *minishell)
{
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	minishell->size = 0;
	minishell->i = 0;
	minishell->env = set_env_array(minishell);
	minishell->envp_array = set_envp_array(minishell->envp);
	if (!minishell->envp_array)
		exit(free_on_exit_error(minishell));
}

void	post_parsing(t_minishell *minishell)
{
	try_access(minishell->cmds, minishell->env);
	minishell->size = set_size(minishell->cmds);
	minishell->pipe_fds = alloc_pipe_fds(minishell);
	minishell->pids = alloc_pids(minishell);
	free(minishell->read_line);
	minishell->read_line = NULL;
	if ((minishell->size > 1 && !minishell->pipe_fds) || !minishell->pids)
		exit(free_on_exit_error(minishell));
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
		if (next->separated_by_space == 0 && (cur->type == word
				|| cur->type == simple_quote || cur->type == double_quote)
			&& (next->type == word || next->type == simple_quote
				|| next->type == double_quote))
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

	parse_error = minishell->read_line;
	add_history(minishell->read_line);
	pre_parsing(minishell);
	if (get_tokens_list(&parse_error, minishell))
		return ;
	if (!minishell->tokens)
		return (free(minishell->read_line));
	merge_adjacent_words(&minishell->tokens);
	expand_tokens(minishell);
	set_commands(minishell);
	post_parsing(minishell);
}
