/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:41:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 16:02:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "free.h"
#include "libft.h"
#include "redirects.h"

int	is_a_builtin(char *str)
{
	return (!ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "echo", 5)
		|| !ft_strncmp(str, "env", 4) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "exit", 5) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6));
}

void	exec_builtsin_in_child(t_minishell *minishell)
{
	char	*cmd;

	minishell->last_status = -1;
	cmd = minishell->cmds->args[0];
	if (!ft_strncmp(cmd, PWD, 4))
		minishell->last_status = pwd(minishell);
	if (!ft_strncmp(cmd, ECHO, 5))
		minishell->last_status = echo(minishell);
	if (!ft_strncmp(cmd, ENV, 4))
		minishell->last_status = env(minishell);
	if (!ft_strncmp(cmd, CD, 3))
		minishell->last_status = cd(minishell);
	if (!ft_strncmp(cmd, EXIT, 5))
		minishell->last_status = ft_exit(minishell, NULL);
	if (!ft_strncmp(cmd, EXPORT, 7))
		minishell->last_status = ft_export(minishell);
	if (!ft_strncmp(cmd, UNSET, 6))
		minishell->last_status = unset(minishell);
	if (minishell->last_status != -1)
	{
		free_minishell(minishell);
		exit(minishell->last_status);
	}
}

void	reset_dup(int *std_copy, t_minishell *minishell)
{
	if (dup2(std_copy[0], STDIN_FILENO) == -1)
		exit_perror(minishell, "dup2");
	close(std_copy[0]);
	if (dup2(std_copy[1], STDOUT_FILENO) == -1)
		exit_perror(minishell, "dup2");
	close(std_copy[1]);
}

void	exec_builtsin_in_parent(t_minishell *minishell)
{
	char	*cmd;
	int		std_copy[2];

	cmd = minishell->cmds->args[0];
	std_copy[0] = dup(STDIN_FILENO);
	std_copy[1] = dup(STDOUT_FILENO);
	set_dup2(minishell);
	if (!ft_strncmp(cmd, CD, 3))
		minishell->last_status = cd(minishell);
	if (!ft_strncmp(cmd, EXIT, 5))
		minishell->last_status = ft_exit(minishell, std_copy);
	if (!ft_strncmp(cmd, EXPORT, 7))
		minishell->last_status = ft_export(minishell);
	if (!ft_strncmp(cmd, UNSET, 6))
		minishell->last_status = unset(minishell);
	reset_dup(std_copy, minishell);
	close_here_doc(minishell->cmds->redirects);
	free_and_set_to_next_commands(&minishell->cmds);
	if (minishell->pids)
		free(minishell->pids);
	minishell->pids = NULL;
}
