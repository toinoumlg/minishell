/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:09 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 16:24:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_utils.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <string.h>

void	fret_enum_tokens_from_args(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (!is_end_of_command(tmp))
	{
		next = tmp->next;
		free(tmp->string);
		free(tmp);
		tmp = next;
	}
	*tokens = tmp;
}

int	get_args_size(t_token *tokens)
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

char	**set_args(t_token **tokens)
{
	t_token	*tmp;
	int		size;
	char	**args;
	int		i;

	size = get_args_size(*tokens);
	tmp = *tokens;
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	memset(args, 0, sizeof(char *) * (size + 1));
	i = 0;
	while (!is_end_of_command(tmp))
	{
		args[i] = ft_strdup(tmp->string);
		if (!args[i])
			return (free_array(args), NULL);
		i++;
		tmp = tmp->next;
	}
	fret_enum_tokens_from_args(tokens);
	i = -1;
	return (args);
}
