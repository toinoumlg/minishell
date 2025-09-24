/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:03:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 17:04:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "parser/commands.h"
#include "parser/token.h"
#include <string.h>

static void	append_new_command(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = *cmds;
	head = tmp;
	if (!tmp)
	{
		*cmds = new_cmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	*cmds = head;
	return ;
}

static t_cmd	*set_new_command(t_minishell *minishell)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_perror(minishell, "malloc ");
	memset(new, 0, sizeof(t_cmd));
	return (new);
}

static void	set_program(t_cmd *new_cmd, t_minishell *minishell)
{
	if (!new_cmd->args)
		return ;
	new_cmd->program = malloc(sizeof(t_file));
	if (!new_cmd->program)
		exit_perror(minishell, "malloc ");
	memset(new_cmd->program, 0, sizeof(t_file));
	new_cmd->program->path = ft_strdup(new_cmd->args[0]);
	if (!new_cmd->program->path)
		exit_perror(minishell, "malloc ");
}

static void	add_new_command(t_minishell *minishell)
{
	t_cmd	*new_cmd;

	new_cmd = set_new_command(minishell);
	append_new_command(&minishell->cmds, new_cmd);
	pick_redirects(new_cmd, minishell);
	set_args(new_cmd, minishell);
	set_program(new_cmd, minishell);
	remove_pipe(&minishell->tokens);
}

void	set_commands(t_minishell *minishell)
{
	while (minishell->tokens)
		add_new_command(minishell);
}
