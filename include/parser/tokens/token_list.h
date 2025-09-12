/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:38:11 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 19:32:04 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "minishell.h"

t_token	*append_new_token(t_token **tokens, t_token *new_token);
t_token	*set_new_token(t_minishell *minishell);
void	add_string_to_token(char *start, int i, t_token *new_token,
			t_minishell *minishell);

#endif