/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 08:28:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"
#include "token_operator.h"
#include "token_string.h"
#include "token_utils.h"
#include <stdlib.h>
#include <string.h>

int	get_tokens_list(char **parse_error, t_minishell *minishell)
{
	int	was_space;

	memset(&minishell->tokens, 0, sizeof(t_token *));
	was_space = 1;
	while (**parse_error)
	{
		if (**parse_error == ';' || **parse_error == '\\')
			return (1);
		else if (is_quote(**parse_error) && extract_quoted_string(parse_error,
				**parse_error, minishell, &was_space))
			return (1);
		else if (is_operator(**parse_error) && add_operator_token(parse_error,
				minishell, &was_space))
			return (1);
		else if (**parse_error == ' ')
		{
			while (**parse_error == ' ')
				(*parse_error)++;
			was_space = 1;
		}
		else if (pick_word(parse_error, minishell, &was_space))
			return (1);
	}
	return (0);
}
