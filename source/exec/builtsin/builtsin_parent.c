/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:41:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:13:56 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "free_utils.h"
#include "libft.h"
#include "minishell.h"
#include "pipes.h"
#include <stdio.h>

static void	cd(char *path)
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

static void	my_exit(t_pipex *pipex, char **env)
{
	if (pipex->i != 0)
		return ;
	printf("exit\n");
	close_pipes(pipex->pipe_fds, pipex->size, pipex->i);
	free_cmds(pipex->cmds);
	free_array(env);
	if (pipex->pipe_fds)
		free(pipex->pipe_fds);
	if (pipex->pids)
		free(pipex->pids);
	exit(0);
}

void	exec_builtin_in_parent(t_pipex *pipex, char **env)
{
	int	i;

	i = pipex->i;
	pipex->pids[i] = -1;
	if (!ft_strncmp(pipex->cmds->args[0], "cd", 3))
		cd(pipex->cmds->args[1]);
	if (!ft_strncmp(pipex->cmds->args[0], "exit", 5))
		my_exit(pipex, env);
}
