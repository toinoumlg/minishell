/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:43:18 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/30 18:54:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	pwd(t_pipex *pipex)
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

static void	echo(t_pipex *pipex)
{
	int	i;

	i = 1;
	if (!pipex->cmds->args[i])
	{
		ft_putstr_fd("\n", 1);
		free_child(pipex);
		exit(1);
	}
	if (!ft_strncmp(pipex->cmds->args[i], "-n", 3))
		i++;
	while (pipex->cmds->args[i])
	{
		ft_putstr_fd(pipex->cmds->args[i++], 1);
		if (pipex->cmds->args[i])
			ft_putstr_fd(" ", 1);
	}
	if (ft_strncmp(pipex->cmds->args[1], "-n", 3))
		ft_putstr_fd("\n", 1);
	free_child(pipex);
	exit(0);
}

static void	env(t_pipex *pipex)
{
	t_envp	*envp;

	envp = *pipex->envp;
	while (envp)
	{
		ft_putstr_fd(envp->line, 1);
		ft_putstr_fd("\n", 1);
		envp = envp->next;
	}
	free_child(pipex);
	exit(0);
}

void	exec_builtin_in_child(t_pipex *pipex)
{
	t_cmd	*cmd;

	cmd = pipex->cmds;
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		pwd(pipex);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		echo(pipex);
	if (!ft_strncmp(pipex->cmds->args[0], "env", 4))
		env(pipex);
}
