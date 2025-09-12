/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:06:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/12 09:57:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "minishell.h"

int		is_builtin_to_exec_in_parent(char *cmd);
void	exit_child_no_execve(t_minishell *minishell);

#endif