/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:18 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:22:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <stdio.h>

static int	pwd_error(t_minishell *minishell)
{
	char	**args;

	args = minishell->cmds->args;
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("bad option: ", 2);
	ft_putchar_fd(args[1][0], 2);
	ft_putchar_fd(args[1][1], 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	pwd(t_minishell *minishell)
{
	char	*path;

	if (minishell->cmds->args[1] && minishell->cmds->args[1][0] == '-')
		pwd_error(minishell);
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
