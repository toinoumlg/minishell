/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:51:09 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/10 17:12:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_free.h"
#include "token_utils.h"
#include <string.h>

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
	i = -1;
	free_tokens_from_args(tokens);
	return (args);
}
