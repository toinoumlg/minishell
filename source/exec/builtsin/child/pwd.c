/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:18 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 21:13:28 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <stdio.h>

static void	pwd_error(t_minishell *minishell)
{
	char	**args;

	args = minishell->cmds->args;
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	if (args[1][0] == '-')
	{
		if (!args[1][1])
			return ;
		ft_putstr_fd("bad option: ", 2);
		ft_putchar_fd(args[1][0], 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(" too many arguments\n", 2);
	}
	free_on_exit_error(minishell);
	exit(1);
}
void	pwd(t_minishell *minishell)
{
	char	path[256];

	if (minishell->cmds->args[1])
		pwd_error(minishell);
	getcwd(path, 256);
	printf("%s\n", path);
	free_on_exit_error(minishell);
	exit(0);
}
