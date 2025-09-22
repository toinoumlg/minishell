/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:32:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:02:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "parser/token.h"

t_token_type	get_operator_type(char *line)
{
	if (*line && *(line + 1))
	{
		if (*line == '>')
		{
			if (!is_operator(*(line + 1)))
				return (output);
			if (*(line + 1) == '>' && !is_operator(*(line + 2)))
				return (append_file);
		}
		if (*line == '<')
		{
			if (!is_operator(*(line + 1)))
				return (input);
			if (*(line + 1) == '<' && !is_operator(*(line + 2)))
				return (here_doc);
		}
		if (*line == '|' && *(line + 1) != '|')
			return (is_pipe);
	}
	return (0);
}

static void	set_operator_string(char **parse_error, t_minishell *minishell,
		t_token *new)
{
	int		size;
	char	*str;
	char	c;

	str = *parse_error;
	if (new->type == append_file || new->type == here_doc)
		size = 2;
	else
		size = 1;
	c = str[size];
	str[size] = 0;
	new->string = ft_strdup(str);
	if (!new->string)
		exit(free_minishell(minishell));
	str[size] = c;
	*parse_error = *parse_error + size;
}

int	check_valid_redirects(t_token *tokens, t_token *new)
{
	if (new && !is_a_redirect(new->type))
		return (0);
	while (tokens)
	{
		if (tokens && tokens->type == space)
			tokens = tokens->next;
		if (!tokens)
			return (0);
		if (is_a_redirect(tokens->type) && ((tokens->next
					&& tokens->next->type != space) || (tokens->next
					&& tokens->next->next)))
		{
			tokens = tokens->next;
			if (tokens->type == space)
				tokens = tokens->next;
			if (!tokens || (tokens->type != double_quote
					&& tokens->type != simple_quote && tokens->type != word))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	check_for_valid_pipe(t_token *tokens, t_token *new)
{
	int	is_empty;

	is_empty = 1;
	if (new->type != is_pipe)
		return (0);
	if (tokens->type == is_pipe)
		return (1);
	while (tokens)
	{
		while (!is_end_of_command(tokens))
		{
			if (tokens->type != space)
				is_empty = 0;
			tokens = tokens->next;
		}
		if (is_empty)
			return (1);
		else if (tokens)
			tokens = tokens->next;
	}
	return (0);
}

int	add_operator(char **parse_error, t_minishell *minishell)
{
	t_token	*new_token;

	new_token = set_new_token(minishell);
	append_new_token(&minishell->tokens, new_token);
	new_token->type = get_operator_type(*parse_error);
	if (!new_token->type)
		return (1);
	if (check_for_valid_pipe(minishell->tokens, new_token)
		|| check_valid_redirects(minishell->tokens, new_token))
		return (1);
	set_operator_string(parse_error, minishell, new_token);
	return (0);
}
