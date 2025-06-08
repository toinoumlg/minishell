/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 23:27:31 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "token_utils.h"
#include <stdio.h>
#include <stdlib.h>

void	add_new_cmds(void)
{
}

void	parse_error(void)
{
	printf("Error parsing ...");
}

void	parse_read_line(char *read_line, t_minishell *minishell)
{
	t_token	*tokens;

	minishell->parse_error = get_tokens_list(read_line, &tokens);
	if (minishell->parse_error)
		return (free(read_line), parse_error());
	
	free_tokens(tokens);
	free(read_line);
}
