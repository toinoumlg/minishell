/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:09 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/12 16:37:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
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

static char	**set_array(int size)
{
	char	**array;

	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	memset(array, 0, sizeof(char *) * (size + 1));
	return (array);
}

char	**set_args(t_token **tokens)
{
	t_token	*tmp;
	char	**args;
	int		i;

	tmp = *tokens;
	args = set_array(get_args_size(*tokens));
	i = 0;
	while (!is_end_of_command(tmp))
	{
		args[i] = ft_strdup(tmp->string);
		if (!args[i])
			return (free_array(args), NULL);
		i++;
		tmp = tmp->next;
	}
	free_tokens_from_args(tokens);
	return (args);
}
