/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:44:58 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 16:55:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTSIN_H
# define BUILTSIN_H

# include "minishell.h"

int		is_a_builtin(char *str);
void	exec_builtsin_in_child(t_minishell *minishell);
void	exec_builtsin_in_parent(t_minishell *minishell);
#endif