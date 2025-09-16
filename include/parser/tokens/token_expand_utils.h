/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:35:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/16 19:43:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_EXPAND_UTILS_H
# define TOKEN_EXPAND_UTILS_H

int		expand_last_status(char *str, t_token *token, t_minishell *minishell);
int		expand_pid(char *str, t_token *token, t_minishell *minishell);
void	insert_word_token(char *str, t_token *token, t_minishell *minishell,
			char *value);

#endif