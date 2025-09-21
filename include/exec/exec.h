/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:33:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 19:46:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int		is_builtin_to_exec_in_parent(t_minishell *minishell);
void	exit_child(t_minishell *minishell);

void	exec(t_minishell *minishell);

#endif