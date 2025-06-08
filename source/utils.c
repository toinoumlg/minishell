/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:02 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/08 06:51:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token %d : [%s]\n", tokens->pos, tokens->string);
		printf("token type: ");
		if (tokens->token_type == word)
			printf("word\n");
		if (tokens->token_type == redirect_output)
			printf("redirect_output\n");
		if (tokens->token_type == redirect_input)
			printf("redirect_input\n");
		if (tokens->token_type == is_pipe)
			printf("pipe\n");
		if (tokens->token_type == here_doc)
			printf("here_doc\n");
		if (tokens->token_type == append_file)
			printf("append_file\n");
		if (tokens->token_type == simple_quote)
			printf("simple_quote\n");
		if (tokens->token_type == double_quote)
			printf("double_quote\n");
		tokens = tokens->next;
	}
}
