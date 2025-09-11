/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:35:41 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 17:37:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_EXPAND_UTILS_H
# define TOKEN_EXPAND_UTILS_H

int	is_var_start(char c);
int	is_var_char(char c);
int	strjoin_inplace(char **dst, const char *src);

#endif