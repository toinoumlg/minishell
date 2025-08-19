/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:46:48 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/09 16:34:22 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/tokens/token_utils.h"

int	check_pipes(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->next && tokens->type == is_pipe)
			return (1);
		if (tokens->next && tokens->type == is_pipe
			&& tokens->next->type == is_pipe)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	check_for_redirect_duplicate(t_token *tokens)
{
	int	input_dup;
	int	output_dup;

	input_dup = 0;
	output_dup = 0;
	while (tokens)
	{
		if (tokens->type == is_pipe)
		{
			input_dup = 0;
			output_dup = 0;
		}
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
