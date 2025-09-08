/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:09 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/08 10:56:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "free_utils.h"
#include "libft.h"
#include "parser/tokens/token_utils.h"
#include "token_free.h"
#include "token_utils.h"
#include <string.h>

static int	get_args_size(t_token *tokens)
{
	int	size;

	size = 0;
	while (!is_end_of_command(tokens))
	{
		size++;
		tokens = tokens->next;
	}
	return (size);
}

static char	**set_array(int size, t_minishell *minishell)
{
	char	**array;

	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		exit(free_on_exit_error(minishell));
	memset(array, 0, sizeof(char *) * (size + 1));
	return (array);
}

char	**set_args(t_cmd *new_cmd, t_minishell *minishell)
{
	t_token	*tmp;
	char	**args;
	int		i;

	tmp = minishell->tokens;
	if (!minishell->tokens || minishell->tokens->type == is_pipe)
		return (NULL);
	args = set_array(get_args_size(minishell->tokens), minishell);
	i = 0;
	while (!is_end_of_command(tmp))
	{
		args[i] = ft_strdup(tmp->string);
		if (!args[i])
		{
			free_cmds(new_cmd);
			free_array(args);
			exit(free_on_exit_error(minishell));
		}
		i++;
		tmp = tmp->next;
	}
	free_tokens_from_args(&minishell->tokens);
	return (args);
}
