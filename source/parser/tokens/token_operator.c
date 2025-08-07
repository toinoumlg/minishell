/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:32:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/20 15:51:35 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "minishell.h"
#include "token_list.h"
#include <stdlib.h>

int	add_pipe(char **read_line, t_minishell *minishell)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	(*read_line)++;
	add_string_to_token("|", 1, new_token, minishell);
	new_token->type = is_pipe;
	append_new_token(&minishell->tokens, new_token);
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

int	add_output_redirect(char **read_line, t_minishell *minishell)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	(*read_line)++;
	if (**read_line == '>')
	{
		(*read_line)++;
		if (is_end_of_read_line(*read_line))
			return (free(new_token), 1);
		add_string_to_token(">>", 2, new_token, minishell);
		new_token->type = append_file;
		append_new_token(&minishell->tokens, new_token);
		return (0);
	}
	if (is_end_of_read_line(*read_line))
		return (free(new_token), 1);
	add_string_to_token(">", 1, new_token, minishell);
	new_token->type = output;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}

int	add_input_redirect(char **read_line, t_minishell *minishell)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	(*read_line)++;
	if (**read_line == '<')
	{
		(*read_line)++;
		if (is_end_of_read_line(*read_line))
			return (free(new_token), 1);
		add_string_to_token("<<", 2, new_token, minishell);
		new_token->type = here_doc;
		append_new_token(&minishell->tokens, new_token);
		return (0);
	}
	if (is_end_of_read_line(*read_line))
		return (free(new_token), 1);
	add_string_to_token("<", 1, new_token, minishell);
	new_token->type = input;
	append_new_token(&minishell->tokens, new_token);
	return (0);
}

int    get_operator_size(char **line)
{
    if (**line == '|' || **line == '<' || **line == '>')
    {
        if ((**line == '<' && *(*line + 1) == '<')
            || (**line == '>' && *(*line + 1) == '>'))
        {
            (*line) += 2;
            return (2);
        }
        (*line)++;
        return (1);
    }
    return (0);
}

t_token *add_operator_token(char **read_line, t_minishell *minishell)
{
    t_token    *new_token;

    new_token = set_new_token(minishell);
    if (!new_token)
        return (NULL);
    if (**read_line == '|')
        new_token->type = is_pipe;
    else if (**read_line == '<' && *(*read_line + 1) != '<')
        new_token->type = input;
    else if (**read_line == '>' && *(*read_line + 1) != '>')
        new_token->type = output;
    else if (**read_line == '<' && *(*read_line + 1) == '<')
        new_token->type = here_doc;
    else if (**read_line == '>' && *(*read_line + 1) == '>')
        new_token->type = append_file;

    add_string_to_token(*read_line, get_operator_size(read_line), new_token, minishell);
    return (append_new_token(&minishell->tokens, new_token));
}
