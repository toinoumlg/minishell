/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:05:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:16:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"

void	echo(t_minishell *minishell)
{
	int i;

	i = 1;
	if (!minishell->cmds->args[i])
	{
		ft_putstr_fd("\n", 1);
		free_on_exit_error(minishell);
		exit(0);
	}
	if (!ft_strncmp(minishell->cmds->args[i], "-n", 3))
		i++;
	while (minishell->cmds->args[i])
	{
		ft_putstr_fd(minishell->cmds->args[i++], 1);
		if (minishell->cmds->args[i])
			ft_putstr_fd(" ", 1);
	}
	if (ft_strncmp(minishell->cmds->args[1], "-n", 3))
		ft_putstr_fd("\n", 1);
	free_on_exit_error(minishell);
	exit(0);
}