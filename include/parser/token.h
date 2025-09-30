/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:33:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/23 18:26:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

/*	List related	*/
t_token	*set_new_token(t_minishell *minishell);
t_token	*append_new_token(t_token **tokens, t_token *new_token);
void	remove_token(t_token **tokens, t_token **to_remove_add);
void	remove_pipe(t_token **tokens);
void	remove_args(t_token **tokens);

void	generate_tokens(t_minishell *minishell);

/*	Word and Quotes tokens	*/
int		add_word(char **parse_error, t_minishell *minishell);
int		add_quoted_string(char **parse_error, char quote,
			t_minishell *minishell);
void	add_space(char **parse_error, t_minishell *minishell);

/*	Operator tokens	*/
int		add_operator(char **read_line, t_minishell *minishell);

void	merge_adjacent(t_minishell *minishell);

/*	Expand	*/
void	expand(t_minishell *minishell);
void	handle_expansion(int *i, t_token *token, t_minishell *minishell);

/*	Utils	*/
int		is_a_redirect(t_token_type type);
int		is_space(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_end_of_command(t_token *token);

#endif