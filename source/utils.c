/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:27:02 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 22:53:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token %d : [%s]\n", tokens->pos, tokens->string);
		if (tokens->is_word)
			printf("is_word\n");
		if (tokens->is_redirect_output)
			printf("is_redirect_output\n");
		if (tokens->is_redirect_input)
			printf("is_redirect_output\n");
		if (tokens->is_pipe)
			printf("is_pipe\n");
		if (tokens->is_here_doc)
			printf("is_here_doc\n");
		if (tokens->is_append_file)
			printf("is_append_file\n");
		tokens = tokens->next;
	}
}
