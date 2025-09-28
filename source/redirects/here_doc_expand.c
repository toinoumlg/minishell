/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 07:48:07 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 15:25:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "minishell.h"
#include "parser/token.h"

int	expand_last_status_here_doc(char *str, char **read_line,
		t_minishell *minishell)
{
	char	*nbr_str;
	char	*tmp;
	int		size;

	nbr_str = ft_itoa(minishell->last_status);
	if (!nbr_str)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	size = ft_strlen(nbr_str);
	tmp = *read_line;
	*read_line = ft_strjoin(tmp, nbr_str);
	free(nbr_str);
	free(tmp);
	str++;
	tmp = *read_line;
	*read_line = ft_strjoin(tmp, str);
	free(tmp);
	return (size);
}

void	append_env_here_doc(char *str, char **read_line, t_minishell *minishell,
		t_envp *expand)
{
	char	*tmp;

	tmp = *read_line;
	*read_line = ft_strjoin(tmp, expand->value);
	if (!*read_line)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	free(tmp);
	tmp = *read_line;
	*read_line = ft_strjoin(tmp, str);
	if (!*read_line)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	free(tmp);
}

static int	expand_env_here_doc(char *str, char **read_line,
		t_minishell *minishell)
{
	t_envp	*expand;
	int		i;
	char	*tmp;
	char	c;

	i = 0;
	while (str[i] && str[i] != '$' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	c = str[i];
	str[i] = 0;
	expand = find_existing_envp(str, minishell->envp);
	str[i] = c;
	if (!expand)
	{
		tmp = *read_line;
		*read_line = ft_strjoin(tmp, str + i);
		free(tmp);
		return (-1);
	}
	append_env_here_doc(str + i, read_line, minishell, expand);
	return (ft_strlen(expand->value) - 1);
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
	else if (*str == '?')
		*i += expand_last_status_here_doc(str, read_line, minishell);
	else
		*i += expand_env_here_doc(str, read_line, minishell);
	free(str);
}

void	expand_here_doc(char **read_line, t_minishell *minishell)
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
