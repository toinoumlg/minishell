/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:36:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 19:32:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_OPERATOR_H
# define TOKEN_OPERATOR_H

# include "minishell.h"

int	add_operator_token(char **read_line, t_minishell *minishell,
		int *was_space);
#endif
