/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:03:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 09:53:30 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_args.h"
#include "commands_list.h"
#include "commands_redirect.h"
#include "free.h"
#include "libft.h"
#include "token_free.h"
#include <string.h>

void	set_program(t_cmd *new_cmd, t_minishell *minishell)
{
	if (!new_cmd->args)
		return ;
	new_cmd->program = malloc(sizeof(t_file));
	if (!new_cmd->program)
	{
		free_cmds(new_cmd);
		exit(free_minishell(minishell));
	}
	memset(new_cmd->program, 0, sizeof(t_file));
	new_cmd->program->path = ft_strdup(new_cmd->args[0]);
	if (!new_cmd->program->path)
	{
		free_cmds(new_cmd);
		exit(free_minishell(minishell));
	}
}

static void	add_new_command(t_minishell *minishell)
{
	t_cmd	*new_cmd;

	new_cmd = set_new_command(minishell);
	append_new_command(&minishell->cmds, new_cmd);
	pick_redirects(new_cmd, minishell);
	new_cmd->args = set_args(new_cmd, minishell);
	set_program(new_cmd, minishell);
	free_pipe(&minishell->tokens);
}

void	set_commands(t_minishell *minishell)
{
	while (minishell->tokens)
		add_new_command(minishell);
}
