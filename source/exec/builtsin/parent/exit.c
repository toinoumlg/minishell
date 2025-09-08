/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/08 13:38:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include "pipes.h"
#include <stdio.h>
#include <stdlib.h>

int	has_alpha(char *str)
{
	if (!str)
		return (1);
	while (str)
	{
		if (ft_isalpha(*str))
			str++;
		else
			return (1);
	}
	return (0);
}

void	my_exit(t_minishell *minishell)
{
	char	*args[2];
	int		result;

	result = 0;
	args[0] = minishell->cmds->args[1];
	args[1] = minishell->cmds->args[2];
	if (minishell->i != 0)
	{
		minishell->pids[minishell->i] = -1;
		return ;
	}
	if (args[0])
	{
		if (args[1])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			minishell->pids[minishell->i] = -2;
			return ;
		}
		if (has_alpha(args[0]))
		{
			printf("exit\n");
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
			free_on_exit_error(minishell);
			exit(2);
		}
		else
			result = ft_atoi(args[0]);
	}
	else
		result = minishell->last_status;
	printf("exit\n");
	close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
	free_on_exit_error(minishell);
	exit(result % 256);
}
