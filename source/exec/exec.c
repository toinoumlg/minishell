/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 14:41:10 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "envp_utils.h"
#include "exec_utils.h"
#include "free.h"
#include "libft.h"
#include "pipes.h"
#include "print_error.h"
#include "set_dup2.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

void	exit_child_no_execve(t_minishell *minishell)
{
	int		exit_value;
	t_cmd	*cmd;

	cmd = minishell->cmds;
	exit_value = print_command_error(cmd->program, cmd->error);
	print_error_file(cmd->error);
	free_on_exit_error(minishell);
	if (!minishell->env)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(exit_value);
}

void	child_process(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	set_signals_child();
	set_dup2(minishell);
	if (!cmd->error)
	{
		exec_builtsin_in_child(minishell);
		execve(cmd->program->path, cmd->args, minishell->envp_array);
	}
	exit_child_no_execve(minishell);
}

void	exec_in_child(t_minishell *minishell)
{
	int	i;

	i = minishell->i;
	minishell->pids[i] = fork();
	if (minishell->pids[i] == -1)
		exit(free_on_exit_error(minishell));
	else if (!minishell->pids[i])
		child_process(minishell);
}

void	try_exec(t_minishell *minishell)
{
	if (!minishell->cmds->args)
		return ;
	if (is_builtin_to_exec_in_parent(minishell->cmds->args[0]))
		exec_builtsin_in_parent(minishell);
	else
		exec_in_child(minishell);
}

static void	close_here_doc(t_file *redirects)
{
	while (redirects)
	{
		if (redirects->type == here_doc)
			close(redirects->fd);
		redirects = redirects->next;
	}
}

static void	change_underscore(char *value, t_envp *envp)
{
	t_envp	*under_score;
	char	*tmp;

	under_score = find_existing_envp("_", envp);
	under_score->value = ft_strdup(value);
	free(under_score->line);
	under_score->line = ft_strjoin(under_score->name, "=");
	tmp = under_score->line;
	under_score->line = ft_strjoin(tmp, value);
	free(tmp);
}

static void	handle_underscore(t_minishell *minishell)
{
	char	**args;
	int		i;

	i = 0;
	args = minishell->cmds->args;
	if (!args)
		return ;
	while (args[i])
		i++;
	if (i == 1)
		change_underscore(minishell->cmds->program->path, minishell->envp);
	else if (i > 1)
		change_underscore(minishell->cmds->args[i - 1], minishell->envp);
}

void	exec(t_minishell *minishell)
{
	while (minishell->cmds)
	{
		do_pipe(minishell);
		handle_underscore(minishell);
		try_exec(minishell);
		close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
		close_here_doc(minishell->cmds->redirects);
		free_and_set_to_next_commands(&minishell->cmds);
		minishell->i++;
	}
	free(minishell->pipe_fds);
	minishell->pipe_fds = NULL;
}
