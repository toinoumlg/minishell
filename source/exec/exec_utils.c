/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:15:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 18:14:51 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "print_error.h"

int	is_builtin_to_exec_in_parent(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	if (!cmd->args)
		return (0);
	return (!cmd->next && (!ft_strncmp(cmd->args[0], "cd", 3)
			|| !ft_strncmp(cmd->args[0], "export", 7)
			|| !ft_strncmp(cmd->args[0], "unset", 6)
			|| !ft_strncmp(cmd->args[0], "exit", 5)));
}

void	exit_child(t_minishell *minishell)
{
	int		exit_value;
	t_cmd	*cmd;

	cmd = minishell->cmds;
	exit_value = print_command_error(cmd->program, cmd->error);
	print_error_file(cmd->error);
	free_minishell(minishell);
	exit(exit_value);
}
