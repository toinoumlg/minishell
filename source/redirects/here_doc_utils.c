/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:11:51 by yalaatik          #+#    #+#             */
/*   Updated: 2025/09/27 19:11:55 by yalaatik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parser/token.h"
#include "redirects.h"
#include "signals.h"
#include <fcntl.h>
#include <readline/readline.h>

void	exit_on_eof(char *lim);

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

int	read_heredoc_line(char **read_line, char *lim,
		t_token_type type, t_minishell *minishell)
{
	*read_line = readline("> ");
	if (!*read_line)
	{
		if (g_heredoc_interrupted)
			open("/dev/tty", O_RDONLY);
		return (0);
	}
	if (!ft_strncmp(*read_line, lim, ft_strlen(lim) + 1))
	{
		free(*read_line);
		return (0);
	}
	if (type == here_doc_word && ft_strchr(*read_line, '$'))
		expand_here_doc(read_line, minishell);
	return (1);
}
