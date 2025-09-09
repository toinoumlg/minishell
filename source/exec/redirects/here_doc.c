/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 16:10:06 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "here_doc_utils.h"
#include "libft.h"
#include "signals.h"
#include "token_list.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <wait.h>

static void	exit_on_eof( char *lim)
{
	write(2,
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		68);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 3);
}

static void	write_here_doc(int fd, char *lim)
{
	char	*read_line;

	set_signals_heredoc();
	while (1)
	{
		read_line = readline(">");
		if (!read_line)
			return (exit_on_eof( lim));
		if (!ft_strncmp(read_line, lim, ft_strlen(lim) + 1))
		{
			free(read_line);
			return ;
		}
		write(fd, read_line, ft_strlen(read_line));
		write(fd, "\n", 1);
		free(read_line);
	}
}

// fd[1] is for writing file
// fd[0] is for reading file
void	set_here_doc(t_file *here_doc_file)
{
	int	fd[2];

	fd[0] = open("/tmp/here_doc", O_CREAT | O_WRONLY);
	fd[1] = open("/tmp/here_doc", O_RDONLY);
	write_here_doc(fd[1], here_doc_file->path);
	here_doc_file->fd = fd[0];
	unlink("/tmp/here_doc");
	close(fd[1]);

}
