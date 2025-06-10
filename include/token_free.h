/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:54:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/10 17:00:33 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_FREE_H
# define TOKEN_FREE_H

# include "minishell.h"

void	free_pipe(t_token **tokens);
void	free_i_token(t_token **tokens, int i);
void	free_tokens_from_args(t_token **tokens);

#endif