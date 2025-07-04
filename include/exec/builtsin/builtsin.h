/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:44:58 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:07:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTSIN_H
# define BUILTSIN_H

# include "minishell.h"

void	exec_builtsin_in_child(t_minishell *minishell);
void	exec_builtsin_in_parent(t_minishell *minishell);

#endif