/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 19:10:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	cd(t_minishell *minishell)
{
	char	*home_path;
	char	*path;

	path = minishell->cmds->args[1];
	if (!path)
	{
		home_path = getenv("HOME");
		chdir(home_path);
		minishell->pids[minishell->i] = -1;
		return ;
	}
	if (!chdir(path))
	{
		minishell->pids[minishell->i] = -1;
		return ;
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	minishell->pids[minishell->i] = -2;
}
