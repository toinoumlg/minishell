/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:47:51 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 12:32:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_utils.h"
#include "minishell.h"
#include <stdlib.h>

void	delete_pipe(t_token **tokens)
{
	t_token	*next;
	t_token	*tmp;

	tmp = *tokens;
	next = tmp->next;
	free(tmp->string);
	free(tmp);
	*tokens = next;
}

int	check_for_pipe(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp && tmp->type == is_pipe)
	{
		delete_pipe(tokens);
		return (1);
	}
	return (0);
}

int	check_for_duplicate(t_token *tokens)
{
	int		input_dup;
	int		output_dup;

	input_dup = 0;
	output_dup = 0;
	while (!is_end_of_command(tokens))
	{
		if (tokens->type == input || tokens->type == here_doc)
			input_dup++;
		if (tokens->type == output || tokens->type == append_file)
			output_dup++;
		tokens = tokens->next;
	}
	if (output_dup > 1 || input_dup > 1)
		return (1);
	else
		return (0);
}
