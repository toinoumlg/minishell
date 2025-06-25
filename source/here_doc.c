/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 22:12:49 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token_list.h"
#include <readline/readline.h>
#include <wait.h>

void	write_in_child(t_cmd *cmd, int here_doc_pipe[2])
{
	char	*read_line;

	while (1)
	{
		read_line = readline(">");
		if (!ft_strncmp(read_line, cmd->infile->path,
				ft_strlen(cmd->infile->path)))
		{
			free(read_line);
			close(here_doc_pipe[1]);
			close(here_doc_pipe[0]);
			exit(0);
		}
		write(here_doc_pipe[1], read_line, ft_strlen(read_line));
		write(here_doc_pipe[1], "\n", 1);
		free(read_line);
	}
}
void	set_here_doc(t_cmd *cmd)
{
	int	here_doc_pipe[2];
	int	fork_pid;

	if (pipe(here_doc_pipe) == -1)
		perror("pipe");
	fork_pid = fork();
	if (fork_pid == -1)
		perror("fork");
	if (!fork_pid)
		write_in_child(cmd, here_doc_pipe);
	else
	{
		waitpid(fork_pid, NULL, 0);
		close(here_doc_pipe[1]);
		if (dup2(here_doc_pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(here_doc_pipe[0]);
	}
}
