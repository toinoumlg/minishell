/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:04:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 11:00:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "minishell.h"

void	alloc_pipe_fds(t_minishell *minishell);
void	alloc_pids(t_minishell *minishell);
void	set_size(t_minishell *minishell);
#endif
