/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:18 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 18:04:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
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
	t_envp	*pwd;

	if (minishell->cmds->args[1] && minishell->cmds->args[1][0] == '-')
		pwd_error(minishell);
	pwd = find_existing_envp("PWD", minishell->envp);
	if (pwd && pwd->value)
		path = pwd->value;
	else
		path = getcwd(NULL, 0);
	if (!path)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", path);
	if (!pwd || !pwd->value)
		free(path);
	return (0);
}
