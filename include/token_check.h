/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:46:33 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/10 16:50:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_CHECK_H
# define TOKEN_CHECK_H

# include "minishell.h"

int		check_for_redirect_duplicate(t_token *tokens);
void	delete_pipe(t_token **tokens);

#endif