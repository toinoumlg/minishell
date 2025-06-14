/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtsin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:10:29 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 18:54:24 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	pwd(t_pipex *pipex)
{
	char	**args;
	char	path[256];

	args = pipex->cmds->args;
	if (args[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": usage: pwd\n", 2);
		free_child(pipex);
		exit(1);
	}
	getcwd(path, 256);
	printf("%s\n", path);
	free_child(pipex);
	exit(0);
}

void	cd(char *path)
{
	char	*home_path;

	if (!path)
	{
		home_path = getenv("HOME");
		chdir(home_path);
		return ;
	}
	if (!chdir(path))
		return ;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	echo(t_pipex *pipex)
{
	if()
}

void	exec_child_builtins(t_pipex *pipex)
{
	t_cmd *cmd;

	cmd = pipex->cmds;
	if (!ft_strncmp(cmd->args[0], "pwd", 3))
		pwd(pipex);
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		echo(pipex);
}