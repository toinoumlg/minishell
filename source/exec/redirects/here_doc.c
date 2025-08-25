/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/25 17:44:19 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "here_doc_utils.h"
#include "libft.h"
#include "token_list.h"
#include <readline/readline.h>
#include <wait.h>

static void	write_in_child(int here_doc_pipe[2], char *here_doc_lim)
{
	char	*read_line;

	while (1)
	{
		read_line = readline(">");
		if (!ft_strncmp(read_line, here_doc_lim, ft_strlen(here_doc_lim) + 1))
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
