/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:19 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 15:34:16 by amalangu         ###   ########.fr       */
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

static void	write_here_doc(int fd, char *lim, t_token_type type,
		t_minishell *minishell)
{
	char	*read_line;

	while (1)
	{
		read_line = readline("> ");
		if (g_sig)
			return ;
		if (!read_line)
			return (exit_on_eof(lim));
		if (!ft_strncmp(read_line, lim, ft_strlen(lim) + 1))
			return (free(read_line));
		if (type == here_doc_word && ft_strchr(read_line, '$'))
			expand_here_doc(read_line, minishell);
		write(fd, read_line, ft_strlen(read_line));
		write(fd, "\n", 1);
		free(read_line);
	}
}

void	save_stds(int *std_copy, t_minishell *minishell)
{
	std_copy[0] = dup(STDIN_FILENO);
	std_copy[1] = dup(STDOUT_FILENO);
	if (std_copy[0] == -1 || std_copy[1] == -1)
		exit_perror(minishell, "dup");
}

void	reset_stds(int *std_copy, t_minishell *minishell)
{
	if (dup2(std_copy[0], STDIN_FILENO) == -1)
		exit_perror(minishell, "dup2");
	close(std_copy[0]);
	if (dup2(std_copy[1], STDOUT_FILENO) == -1)
		exit_perror(minishell, "dup2");
	close(std_copy[1]);
}

// fd[1] is for writing file
// fd[0] is for reading file
int	set_here_doc(t_file *here_doc_file, t_minishell *minishell)
{
	int	fd[2];
	int	std_copy[2];

	g_sig = 0;
	save_stds(std_copy, minishell);
	set_signals_heredoc();
	fd[1] = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	fd[0] = open("/tmp/here_doc", O_RDONLY);
	unlink("/tmp/here_doc");
	write_here_doc(fd[1], here_doc_file->path, here_doc_file->type, minishell);
	close(fd[1]);
	here_doc_file->fd = fd[0];
	set_signals();
	reset_stds(std_copy, minishell);
	if (g_sig)
	{
		minishell->last_status = 130;
		free_cmds(minishell->cmds);
		minishell->cmds = NULL;
		return (1);
	}
	return (0);
}
