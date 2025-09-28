/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:35:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 14:16:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "envp.h"
#include "exec.h"
#include "free.h"
#include "libft.h"
#include "redirects.h"
#include "signals.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*	Child process execution: sets up signals and redirects,
	Attempts builtin execution then tries execve
	If not exited after execve will print associated error	*/
void	child_process(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmds;
	clear_history();
	set_signals_child();
	set_dup2(minishell);
	if (!cmd->args && cmd->redirects)
		create_files(minishell);
	if (!cmd->error)
	{
		exec_builtsin_in_child(minishell);
		execve(cmd->program->path, cmd->args, minishell->envp_array);
	}
	exit_child(minishell);
}

/*	Forks and check for any error	*/
void	exec_in_child(t_minishell *minishell)
{
	int	i;

	i = minishell->i;
	minishell->pids[i] = fork();
	if (minishell->pids[i] == -1)
		exit_perror(minishell, "fork");
	else if (!minishell->pids[i])
		child_process(minishell);
}

void	exec(t_minishell *minishell)
{
	if (!minishell->cmds)
		return ;
	if (is_builtin_to_exec_in_parent(minishell))
		return (exec_builtsin_in_parent(minishell));
	while (minishell->cmds)
	{
		do_pipe(minishell);
		underscore(minishell);
		exec_in_child(minishell);
		close_pipes(minishell->pipe_fds, minishell->size, minishell->i);
		close_here_doc(minishell->cmds->redirects);
		free_and_set_to_next_commands(&minishell->cmds);
		minishell->i++;
	}
	if (minishell->pipe_fds)
		free(minishell->pipe_fds);
	minishell->pipe_fds = NULL;
}
