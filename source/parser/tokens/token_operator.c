/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:32:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 08:31:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list.h"
#include <stdlib.h>

int	add_pipe(char **read_line, t_token **tokens)
{
	t_token	*new;

	new = set_new_token();
	(*read_line)++;
	if (!new)
		return (1);
	if (add_string_to_token("|", 1, new))
		return (1);
	new->type = is_pipe;
	append_new_token(tokens, new);
	return (0);
}

static int	is_end_of_read_line(char *read_line)
{
	while (read_line && *read_line != '\n' && *read_line != '\000')
	{
		if (*read_line == ' ')
			read_line++;
		else
			return (0);
	}
	return (1);
}

int	add_output_redirect(char **read_line, t_token **tokens)
{
	t_token	*new;

	new = set_new_token();
	if (!new)
		return (1);
	(*read_line)++;
	if (**read_line == '>')
	{
		(*read_line)++;
		if (is_end_of_read_line(*read_line) || add_string_to_token(">>", 2,
				new))
			return (free(new), 1);
		new->type = append_file;
		append_new_token(tokens, new);
		return (0);
	}
	else if (is_end_of_read_line(*read_line) || add_string_to_token(">", 1,
			new))
		return (free(new), 1);
	new->type = output;
	append_new_token(tokens, new);
	return (0);
}

int	add_input_redirect(char **read_line, t_token **tokens)
{
	t_token	*new;

	new = set_new_token();
	if (!new)
		return (1);
	(*read_line)++;
	if (**read_line == '<')
	{
		(*read_line)++;
		if (is_end_of_read_line(*read_line) || add_string_to_token("<<", 2,
				new))
			return (free(new), 1);
		new->type = here_doc;
		append_new_token(tokens, new);
		return (0);
	}
	else if (is_end_of_read_line(*read_line) || add_string_to_token("<", 1,
			new))
		return (free(new), 1);
	new->type = input;
	append_new_token(tokens, new);
	return (0);
}

int	add_operator_token(char **read_line, t_token **tokens)
{
	if (**read_line == '<' && add_input_redirect(read_line, tokens))
		return (1);
	else if (**read_line == '>' && add_output_redirect(read_line, tokens))
		return (1);
	else if (**read_line == '|' && add_pipe(read_line, tokens))
		return (1);
	return (0);
}
