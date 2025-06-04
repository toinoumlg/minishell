/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/04 19:06:17 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	add_new_cmds(void)
{
}

int	add_pipe(char **read_line, t_token **tokens)
{
	(void)read_line;
	(void)tokens;
	return (0);
}

int	is_metacharacter(char c)
{
	if (c == ' ' || c == '	' || c == '\n' || c == '|' || c == '&' || c == ';'
			|| c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

void	add_word_to_token(char *start, int i, t_token **tokens)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*new;

	tmp = *tokens;
	head = *tokens;
	new = malloc(sizeof(t_token));
	new->word = start;
	new->word[i + 1] = 0;
	new->next = NULL;
	if (!tmp)
	{
		*tokens = new;
		return ;
	}
	while (tmp)
		tmp = tmp->next;
	tmp = new;
	*tokens = head;
}

int	pick_word(char **read_line, t_token **tokens)
{
	char	*end;
	char	*start;
	int		i;

	i = 0;
	end = *read_line;
	start = *read_line;
	while (!is_metacharacter(end[i]))
		i++;
	add_word_to_token(start, i, tokens);
	*read_line = end + i;
	return (0);
}

int	extract_quoted_string(char **read_line, char quote, t_token **tokens)
{
	(void)read_line;
	(void)tokens;
	(void)quote;
	return (0);
}

int	add_input_redirect(char **read_line, t_token **tokens)
{
	(void)read_line;
	(void)tokens;
	return (0);
}
int	add_output_redirect(char **read_line, t_token **tokens)
{
	(void)read_line;
	(void)tokens;
	return (0);
}

int	add_operator_token(char *read_line, t_token *tokens)
{
	if (*read_line == '<' && add_input_redirect(&read_line, &tokens))
		return (1);
	else if (*read_line == '>' && add_output_redirect(&read_line, &tokens))
		return (1);
	else if (*read_line == '|' && add_pipe(&read_line, &tokens))
		return (1);
	return (0);
}

int	is_operator(char read_char)
{
	if (read_char == '<' || read_char == '>' || read_char == '|')
		return (1);
	else
		return (0);
}

int	get_tokens_list(char *read_line, t_token *tokens)
{
	while (*read_line)
	{
		if (*read_line == '"' && extract_quoted_string(&read_line, '"',
				&tokens))
			return (1);
		else if (*read_line == '\'' && extract_quoted_string(&read_line, '\'',
			&tokens))
			return (1);
		else if (is_operator(*read_line) && add_operator_token(read_line,
				tokens))
			return (1);
		else if (pick_word(&read_line, &tokens))
			return (1);
		else if (*read_line == ' ')
			read_line++;
	}
	return (0);
}

void	parse_error(void)
{
	printf("Error parsing ...");
}

void	parse_read_line(char *read_line, t_minishell *minishell)
{
	minishell->parse_error = get_tokens_list(read_line, minishell->tokens);
	if (minishell->parse_error)
		return (free(read_line), parse_error());
	free(read_line);
}
