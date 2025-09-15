/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:41:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 16:55:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "echo.h"
#include "env.h"
#include "exit.h"
#include "export.h"
#include "libft.h"
#include "pwd.h"
#include "unset.h"

int	is_a_builtin(char *str)
{
	return (!ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "echo", 5)
		|| !ft_strncmp(str, "env", 4) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "exit", 5) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6));
}

void	exec_builtsin_in_child(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		pwd(minishell);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		echo(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "env", 4))
		env(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "cd", 3))
		cd(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "exit", 5))
		my_exit(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "export", 7))
		my_export(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "unset", 6))
		unset(minishell);
}

void	exec_builtsin_in_parent(t_minishell *minishell)
{
	if (!ft_strncmp(minishell->cmds->args[0], "cd", 3))
		cd(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "exit", 5))
		my_exit(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "export", 7))
		my_export(minishell);
	if (!ft_strncmp(minishell->cmds->args[0], "unset", 6))
		unset(minishell);
}
