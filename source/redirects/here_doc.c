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

static void	exit_on_eof(char *lim)
{
	write(2,
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		68);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 3);
}

static void	handle_here_doc_expansion(int *i, char **read_line,
		t_minishell *minishell)
{
	char	*str;

	str = ft_strdup(*read_line + *i + 1);
	if (!str)
		exit_perror(minishell, "malloc");
	else if (!*str || *str == ' ' || *str == '/')
		(*read_line)[(*i)++] = '$';
	else if (*str == '$')
		*i += expand_pid_here_doc(str, read_line, minishell);
	else if (*str == '?')
		*i += expand_last_status_here_doc(str, read_line, minishell);
	else
		*i += expand_env_here_doc(str, read_line, minishell);
	free(str);
}

/*	Expands variable on read_line string.
	Works like token expansion but modifies the read_line string directly	*/
static void	expand_here_doc(char **read_line, t_minishell *minishell)
{
	int	i;

	i = 0;
	while ((*read_line)[i])
	{
		if ((*read_line)[i] == '$')
		{
			(*read_line)[i] = 0;
			handle_here_doc_expansion(&i, read_line, minishell);
		}
		i++;
	}
}

static void write_here_doc(int fd, char *lim, t_token_type type, t_minishell *minishell)
{
    char *read_line;

    signal(SIGINT, heredoc_sigint_handler);  // Changement direct
    
    while (1) {
        read_line = readline("> ");
        
        if (!read_line) {
            if (g_heredoc_interrupted)
                open("/dev/tty", O_RDONLY);
            break;
        }
        
        if (!ft_strncmp(read_line, lim, ft_strlen(lim) + 1)) {
            free(read_line);
            break;
        }
        
        if (type == here_doc_word && ft_strchr(read_line, '$'))
            expand_here_doc(&read_line, minishell);
        write(fd, read_line, ft_strlen(read_line));
        write(fd, "\n", 1);
        free(read_line);
    }
    
    signal(SIGINT, sigint_handler_main);  // Restauration directe
    
    if (g_heredoc_interrupted == 1) {
        minishell->last_status = 130;
        g_heredoc_interrupted = 0;
        return;
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
	write_here_doc(fd[1], here_doc_file->path, here_doc_file->type, minishell);
	close(fd[1]);
	fd[0] = open("/tmp/here_doc", O_RDONLY);
	here_doc_file->fd = fd[0];
	unlink("/tmp/here_doc");
}
