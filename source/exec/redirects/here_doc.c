/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/08 10:33:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "here_doc_utils.h"
#include "libft.h"
#include "token_list.h"
#include <readline/readline.h>
#include <wait.h>

static void	exit_on_eof(int here_doc_pipe[2], char *lim)
{
	close(here_doc_pipe[1]);
	close(here_doc_pipe[0]);
	write(2,
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		68);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 3);
	exit(0);
}

static void	write_in_child(int here_doc_pipe[2], char *lim)
{
	char	*read_line;

	while (1)
	{
		read_line = readline(">");
		if (!read_line)
			exit_on_eof(here_doc_pipe, lim);
		if (!ft_strncmp(read_line, lim, ft_strlen(lim) + 1))
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

void	set_here_doc(t_file *here_doc_file)
{
	int	pid;
	int	here_doc_pipe[2];

	if (pipe(here_doc_pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		write_in_child(here_doc_pipe, here_doc_file->path);
	else
	{
		waitpid(pid, NULL, 0);
		here_doc_file->fd = here_doc_pipe[0];
		close(here_doc_pipe[1]);
	}
}
