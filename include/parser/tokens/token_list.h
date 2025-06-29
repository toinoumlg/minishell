/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:38:11 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 22:47:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "minishell.h"

void	append_new_token(t_token **tokens, t_token *new);
t_token	*set_new_token(void);
int		add_string_to_token(char *start, int i, t_token *new);

#endif