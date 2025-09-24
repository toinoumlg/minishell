/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:09 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 17:03:41 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parser/token.h"
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
		exit(free_minishell(minishell));
	memset(array, 0, sizeof(char *) * (size + 1));
	return (array);
}

void	set_args(t_cmd *new_cmd, t_minishell *minishell)
{
	int		i;
	t_token	*tokens;

	if (!minishell->tokens || minishell->tokens->type == is_pipe)
		return ;
	new_cmd->args = set_array(get_args_size(minishell->tokens), minishell);
	if (!new_cmd->args)
		exit_perror(minishell, "malloc");
	i = 0;
	tokens = minishell->tokens;
	while (!is_end_of_command(tokens))
	{
		new_cmd->args[i] = ft_strdup(tokens->string);
		if (!new_cmd->args[i])
			exit_perror(minishell, "malloc");
		i++;
		tokens = tokens->next;
	}
	new_cmd->args[i] = NULL;
	remove_args(&minishell->tokens);
}
