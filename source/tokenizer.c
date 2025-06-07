/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 22:53:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list.h"
#include "token_operator.h"
#include "token_utils.h"
#include "utils.h"

int	extract_quoted_string(char **read_line, char quote, t_token **tokens)
{
	(void)read_line;
	(void)tokens;
	(void)quote;
	return (0);
}

int	pick_word(char **read_line, t_token **tokens)
{
	t_token	*new;
	char	*start;
	int		i;

	start = *read_line;
	if (!**read_line)
		return (0);
	i = get_word_size(read_line);
	new = set_new_token();
	if (!new || i <= 0 || add_string_to_token(start, i, new))
		return (1);
	new->is_word = 1;
	append_new_token(tokens, new);
	return (0);
}

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
