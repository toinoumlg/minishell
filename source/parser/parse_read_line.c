/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/04 14:51:04 by amalangu         ###   ########.fr       */
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
#include "token_expand.h"
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

void	pre_parsing(t_minishell *minishell)
{
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	minishell->size = 0;
	minishell->i = 0;
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
	if ((minishell->size > 1 && !minishell->pipe_fds) || !minishell->pids)
		exit(free_on_exit_error(minishell));
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
	expand_tokens(minishell);
	set_commands(minishell);
	post_parsing(minishell);
}
