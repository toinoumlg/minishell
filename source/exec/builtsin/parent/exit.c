/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:16:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "pipes.h"
#include <stdio.h>
#include <stdlib.h>

void	my_exit(t_minishell *minishell)
{
	if (minishell->i != 0)
		return ;
	printf("exit\n");
	close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
	free_on_exit_error(minishell);
	exit(0);
}
