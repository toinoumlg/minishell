/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/04 13:01:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"
#include "token_check.h"
#include "token_operator.h"
#include "token_string.h"
#include "token_utils.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int	get_tokens_list(char **parse_error, t_minishell *minishell)
{
	memset(&minishell->tokens, 0, sizeof(t_token *));
	while (**parse_error)
	{
		if (is_quote(**parse_error) && extract_quoted_string(parse_error,
				**parse_error, minishell))
			return (parsing_error(*parse_error, minishell));
		else if (is_operator(**parse_error) && add_operator_token(parse_error,
				minishell))
			return (parsing_error(*parse_error, minishell));
		else if (**parse_error == ' ')
			(*parse_error)++;
		else if (pick_word(parse_error, minishell))
			return (parsing_error(*parse_error, minishell));
	}
	if (check_pipes(minishell->tokens))
		return (parsing_error(*parse_error, minishell));
	free(minishell->read_line);
	minishell->read_line = NULL;
	return (0);
}
