/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:04:34 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 13:45:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

void	close_pipes(int (*pipe_fds)[2], int size, int i);
void	dup2_pipes(int (*pipe_fds)[2], int size, int i, t_minishell *minishell);
void	do_pipe(t_minishell *minishell);

#endif