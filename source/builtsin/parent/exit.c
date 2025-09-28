/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 14:13:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "redirects.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

static int	is_nbr(char *str)
{
	if (!*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (str && *str != 0)
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}

static int	ft_strlen_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}

static void	reset_dup(int *std_copy, t_minishell *minishell)
{
	if (!std_copy)
		return ;
	if (dup2(std_copy[0], STDIN_FILENO) == -1)
		exit_perror(minishell, "dup2");
	close(std_copy[0]);
	if (dup2(std_copy[1], STDOUT_FILENO) == -1)
		exit_perror(minishell, "dup2");
	close(std_copy[1]);
}

int	exit_alpha(t_minishell *minishell, int *std_copy)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(minishell->cmds->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
	free_minishell(minishell);
	reset_dup(std_copy, minishell);
	clear_history();
	return (2);
}

int	ft_exit(t_minishell *minishell, int *std_copy)
{
	int	result;
	int	args_size;

	result = 0;
	args_size = ft_strlen_array(minishell->cmds->args);
	if (args_size > 1 && !is_nbr(minishell->cmds->args[1]))
		exit(exit_alpha(minishell, std_copy));
	else if (args_size > 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (args_size == 2)
		result = ft_atoi(minishell->cmds->args[1]);
	else
		result = minishell->last_status;
	ft_putstr_fd("exit\n", 1);
	close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
	reset_dup(std_copy, minishell);
	free_minishell(minishell);
	clear_history();
	exit(result % 256);
}
