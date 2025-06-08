/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 22:58:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_operator.h"
#include "token_utils.h"
#include "token_string.h"
#include "utils.h"


int	get_tokens_list(char *read_line, t_token **tokens)
{
	*tokens = 0;
	while (*read_line)
	{
		if (is_quote(*read_line) && extract_quoted_string(&read_line,
				*read_line, tokens))
			return (1);
		else if (is_operator(*read_line) && add_operator_token(&read_line,
				tokens))
			return (1);
		else if (*read_line == ' ')
			read_line++;
		else if (pick_word(&read_line, tokens))
			return (1);
	}
	print_tokens(*tokens);
	return (0);
}
