/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 14:34:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parser/token.h"
#include "redirects.h"
#include "signals.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <wait.h>

int	read_heredoc_line(char **read_line, char *lim,
		t_token_type type, t_minishell *minishell);

void	exit_on_eof(char *lim)
{
	write(2,
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		68);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 3);
}

/*	Expands variable on read_line string.
	Works like token expansion but modifies the read_line string directly	*/

static void	w_hdoc(int fd, char *lim, t_token_type type, t_minishell *minishell)
{
	char	*read_line;

	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		if (!read_heredoc_line(&read_line, lim, type, minishell))
			break ;
		write(fd, read_line, ft_strlen(read_line));
		write(fd, "\n", 1);
		free(read_line);
	}
	signal(SIGINT, sigint_handler_main);
	if (g_heredoc_interrupted == 1)
	{
		minishell->last_status = 130;
		g_heredoc_interrupted = 0;
		return ;
	}
	if (!read_line)
		exit_on_eof(lim);
}

// fd[1] is for writing file
// fd[0] is for reading file
void	set_here_doc(t_file *here_doc_file, t_minishell *minishell)
{
	int	fd[2];

	fd[1] = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	w_hdoc(fd[1], here_doc_file->path, here_doc_file->type, minishell);
	close(fd[1]);
	fd[0] = open("/tmp/here_doc", O_RDONLY);
	here_doc_file->fd = fd[0];
	unlink("/tmp/here_doc");
}
