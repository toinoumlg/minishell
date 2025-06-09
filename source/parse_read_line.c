/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 16:14:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_access.h"
#include "commands_list.h"
#include "free.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	parse_error(void)
{
	printf("Error parsing ...");
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

void	free_token(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->string);
		free(tokens);
		tokens = next;
	}
}

void	parse_read_line(char *read_line, t_minishell *minishell, char **env)
{
	t_token	*tokens;

	memset(&tokens, 0, sizeof(t_token *));
	minishell->parse_error = get_tokens_list(read_line, &tokens);
	if (minishell->parse_error)
		return (free(read_line), parse_error());
	// expand_tokens();
	if (set_commands(&tokens, minishell))
		return (free(read_line), free_token(tokens), free_cmds(minishell->cmds),
			parse_error());
	try_access(minishell->cmds, env);
	// free(read_line);
}
