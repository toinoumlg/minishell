/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:05:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/16 14:05:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"

int	is_only_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i++] != '-' || !str[i])
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo(t_minishell *minishell)
{
	int	i;

	i = 1;
	if (!minishell->cmds->args[i])
	{
		ft_putstr_fd("\n", 1);
		free_minishell(minishell);
		exit(0);
	}
	while (!is_only_n(minishell->cmds->args[i]))
		i++;
	while (minishell->cmds->args[i])
	{
		ft_putstr_fd(minishell->cmds->args[i++], 1);
		if (minishell->cmds->args[i])
			ft_putstr_fd(" ", 1);
	}
	if (is_only_n(minishell->cmds->args[1]))
		ft_putstr_fd("\n", 1);
	free_minishell(minishell);
	exit(0);
}
