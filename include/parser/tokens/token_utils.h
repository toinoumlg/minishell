/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:36:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 15:59:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include "minishell.h"

int	is_a_redirect(t_enum_token type);
int	is_space(char c);
int	is_quote(char c);
int	is_operator(char c);
int	is_end_of_command(t_token *token);

#endif