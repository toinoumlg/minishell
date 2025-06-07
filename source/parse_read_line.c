/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:03 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 18:20:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
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
			|| c == '(' || c == ')' || c == '<' || c == '>' || c == 0)
		return (1);
	else
		return (0);
}

int	add_string_to_token(char *start, int i, t_token *new)
{
	new->string = ft_strdup(start);
	if (!new->string)
		return (1);
	new->string[i] = 0;
	return (0);
}

t_token	*set_new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_token));
	return (new);
}

void	append_new_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;
	t_token	*head;
	int		i;

	i = 0;
	tmp = *tokens;
	head = tmp;
	if (!tmp)
	{
		new->pos = i;
		*tokens = new;
		return ;
	}
	while (tmp->next && ++i)
		tmp = tmp->next;
	++i;
	tmp->next = new;
	new->pos = i;
	*tokens = head;
	return ;
}

int	get_word_size(char **read_line)
{
	int	i;

	i = 0;
	while (!is_metacharacter(**read_line) && ++i)
		(*read_line)++;
	return (i);
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

int	extract_quoted_string(char **read_line, char quote, t_token **tokens)
{
	(void)read_line;
	(void)tokens;
	(void)quote;
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
		if (add_string_to_token("<<", 2, new))
			return (1);
		new->is_here_doc = 1;
		append_new_token(tokens, new);
		return (0);
	}
	else if (add_string_to_token("<", 1, new))
		return (1);
	new->is_redirect_input = 1;
	append_new_token(tokens, new);
	return (0);
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
		if (add_string_to_token(">>", 2, new))
			return (1);
		new->is_append_file = 1;
		append_new_token(tokens, new);
		return (0);
	}
	else if (add_string_to_token(">", 1, new))
		return (1);
	new->is_redirect_output = 1;
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

int	is_operator(char read_c)
{
	if (read_c == '<' || read_c == '>' || read_c == '|')
		return (1);
	else
		return (0);
}

int	is_quote(char read_c)
{
	if ((read_c == '"' || read_c == '\''))
		return (1);
	else
		return (0);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token %d:[%s]\nis_word [%d]\nis_redirect_input[%d]\nis_here_doc [%d]\nis_redirect_output [%d]\nis_append_file [%d]\n",
			tokens->pos, tokens->string, tokens->is_word,tokens->is_redirect_input,
			tokens->is_here_doc, tokens->is_redirect_output,
			tokens->is_append_file);
		tokens = tokens->next;
	}
	printf("\n");
}

int	get_tokens_list(char *read_line, t_token **tokens)
{
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
		else
			(pick_word(&read_line, tokens));
	}
	print_tokens(*tokens);
	return (0);
}

void	parse_error(void)
{
	printf("Error parsing ...");
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->string)
			free(tokens->string);
		free(tokens);
		tokens = tmp;
	}
}

void	parse_read_line(char *read_line, t_minishell *minishell)
{
	t_token	*tokens;

	tokens = 0;
	minishell->parse_error = get_tokens_list(read_line, &tokens);
	if (minishell->parse_error)
		return (free(read_line), parse_error());
	printf("%s\n", read_line);
	free_tokens(tokens);
	free(read_line);
}
