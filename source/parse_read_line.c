/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/12 16:50:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access.h"
#include "commands.h"
#include "free.h"
#include "token.h"
#include <stdlib.h>


void	parse_read_line(char *read_line, t_minishell *minishell, char **env)
{
	t_token	*tokens;

	if (get_tokens_list(read_line, &tokens))
		return (free_get_token_list(read_line, tokens));
	// expand_tokens();
	if (set_commands(&tokens, &minishell->cmds))
		return (free_set_commands(read_line, tokens, minishell->cmds));
	try_access(minishell->cmds, env);
	free(read_line);
}
