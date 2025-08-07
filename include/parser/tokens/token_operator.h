/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:36:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/20 15:46:36 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_OPERATOR_H
# define TOKEN_OPERATOR_H

# include "minishell.h"

int	check_pipes(t_token *tokens);
t_token *add_operator_token(char **read_line, t_minishell *minishell);

#endif
