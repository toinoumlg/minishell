/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/09 16:40:26 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"
#include "token_check.h"
#include "token_operator.h"
#include "token_string.h"
#include "parser/tokens/token_utils.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int get_tokens_list(char **parse_error, t_minishell *minishell)
{
    memset(&minishell->tokens, 0, sizeof(t_token *));
    int was_space = 1; // initialement vrai (avant le premier token)

    while (**parse_error)
	{
		if (**parse_error == ' ')
		{
			was_space = 1;
			(*parse_error)++;
		}
		else if (is_quote(**parse_error))
		{
			t_token *new = extract_quoted_string(parse_error, **parse_error, minishell);
			if (new)
				new->separated_by_space = was_space;
			was_space = 0;
		}
		else if (is_operator_char(**parse_error))
		{
			t_token *new = add_operator_token(parse_error, minishell);
			if (new)
				new->separated_by_space = was_space;
			was_space = 0;
		}
		else
		{
			t_token *new = pick_word(parse_error, minishell);
			if (new)
				new->separated_by_space = was_space;
			was_space = 0;
		}
	}
    return (0);
}
