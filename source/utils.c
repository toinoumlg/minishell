/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:02 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/10 16:45:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_commands(t_cmd *cmds)
{
	int	i;
	int	j;

	j = 0;
	while (cmds)
	{
		i = 0;
		printf("cmd %d: ", j++);
		if (cmds->next)
			printf("pipe to next\n");
		if (!cmds->next)
			printf("is last\n");
		if (cmds->infile)
			printf("infile path: [%s]\n", cmds->infile->path);
		if (cmds->outfile)
			printf("outfile path: [%s]\n", cmds->outfile->path);
		printf("args: ");
		while (cmds->args[i])
			printf("[%s] ", cmds->args[i++]);
		printf("\n");
		cmds = cmds->next;
	}
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("token %d : [%s]\n", i, tokens->string);
		printf("token type: ");
		if (tokens->type == word)
			printf("word\n");
		if (tokens->type == output)
			printf("output\n");
		if (tokens->type == input)
			printf("input\n");
		if (tokens->type == is_pipe)
			printf("pipe\n");
		if (tokens->type == here_doc)
			printf("here_doc\n");
		if (tokens->type == append_file)
			printf("append_file\n");
		if (tokens->type == simple_quote)
			printf("simple_quote\n");
		if (tokens->type == double_quote)
			printf("double_quote\n");
		tokens = tokens->next;
		i++;
	}
}
