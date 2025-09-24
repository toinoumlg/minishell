/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:25:17 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/23 18:43:20 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parser/token.h"
#include <stdlib.h>
#include <string.h>

int	check_redirects(t_token *tokens)
{
	while (tokens)
	{
		if (tokens && tokens->type == space)
			tokens = tokens->next;
		if (tokens && is_a_redirect(tokens->type))
		{
			tokens = tokens->next;
			if (!tokens)
				return (1);
			if (tokens->type == space)
				tokens = tokens->next;
			if (!tokens || (tokens->type != double_quote
					&& tokens->type != simple_quote && tokens->type != word))
				return (1);
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (0);
}

static int	check_pipes(t_token *tokens)
{
	int	is_empty;
	int	pipe_count;

	is_empty = 1;
	pipe_count = 0;
	while (tokens)
	{
		while (!is_end_of_command(tokens))
		{
			if (tokens->type != space)
				is_empty = 0;
			tokens = tokens->next;
		}
		if (is_empty && pipe_count)
			return (1);
		else if (tokens)
		{
			pipe_count++;
			is_empty = 1;
			tokens = tokens->next;
		}
	}
	return (0);
}

static int	get_tokens(char **parse_error, t_minishell *minishell)
{
	memset(&minishell->tokens, 0, sizeof(t_token *));
	while (**parse_error)
	{
		if (**parse_error == ';' || **parse_error == '\\')
			return (1);
		else if (is_quote(**parse_error) && add_quoted_string(parse_error,
				**parse_error, minishell))
			return (1);
		else if (is_operator(**parse_error) && add_operator(parse_error,
				minishell))
			return (1);
		else if (is_space(**parse_error))
			add_space(parse_error, minishell);
		else if (add_word(parse_error, minishell))
			return (1);
	}
	return (check_redirects(minishell->tokens)
		|| check_pipes(minishell->tokens));
}

void	syntax_error(char *parse_error, t_minishell *minishell)
{
	minishell->last_status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (!*parse_error)
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(*parse_error, 2);
	ft_putstr_fd("'\n", 2);
	if (minishell->tokens)
		free_tokens(minishell->tokens);
	free(minishell->read_line);
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	if (minishell->paths)
		free_array(minishell->paths);
	minishell->read_line = NULL;
	minishell->tokens = NULL;
	minishell->envp_array = NULL;
	minishell->paths = NULL;
}

/*	Creates a list of tokens from readline()
	parse_error tracks position in input for syntax error	*/
void	generate_tokens(t_minishell *minishell)
{
	char	*parse_error;

	parse_error = minishell->read_line;
	if (get_tokens(&parse_error, minishell))
		return (syntax_error(parse_error, minishell));
	free(minishell->read_line);
	minishell->read_line = NULL;
	if (!minishell->tokens)
		return ;
	expand(minishell);
	merge_adjacent(minishell);
}
