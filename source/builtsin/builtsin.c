/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:41:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/14 13:11:18 by amalangu         ###   ########.fr       */
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
