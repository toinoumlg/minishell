/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:56:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 15:55:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_expand_utils.h"

int	expand_pid(char *str, t_token *token, t_minishell *minishell)
{
	char	*pid;
	char	*tmp;
	int		size;

	pid = ft_itoa(getpid());
	if (!pid)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	size = ft_strlen(pid);
	tmp = token->string;
	token->string = ft_strjoin(tmp, pid);
	free(pid);
	free(tmp);
	str++;
	tmp = token->string;
	token->string = ft_strjoin(tmp, str);
	free(tmp);
	return (size);
}

int	expand_last_status(char *str, t_token *token, t_minishell *minishell)
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
	tmp = token->string;
	token->string = ft_strjoin(tmp, nbr_str);
	free(nbr_str);
	free(tmp);
	str++;
	tmp = token->string;
	token->string = ft_strjoin(tmp, str);
	free(tmp);
	return (size);
}

void	append_env_to_string(char *str, t_token *token, t_minishell *minishell,
		t_envp *expand, int i)
{
	char	*tmp;

	tmp = token->string;
	token->string = ft_strjoin(tmp, expand->value);
	if (!token->string)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	free(tmp);
	tmp = token->string;
	token->string = ft_strjoin(tmp, str + i);
	if (!token->string)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	free(tmp);
}

t_envp	*get_env_and_update_str(int *i, char *str, t_minishell *minishell)
{
	char	c;
	t_envp	*expand;

	while (str[*i] && str[*i] != '$' && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	c = str[*i];
	str[*i] = 0;
	expand = find_existing_envp(str, minishell->envp);
	str[*i] = c;
	return (expand);
}

static int	expand_env(char *str, t_token *token, t_minishell *minishell)
{
	t_envp	*expand;
	int		i;
	char	*tmp;
	int		size;

	i = 0;
	expand = get_env_and_update_str(&i, str, minishell);
	if (expand)
	{
		size = ft_strlen(expand->value) - 1;
		append_env_to_string(str, token, minishell, expand, i);
	}
	else
	{
		tmp = token->string;
		size = -1;
		token->string = ft_strjoin(tmp, str + i);
		free(tmp);
	}
	return (size);
}

void	handle_dollard_expansion(int *i, t_token *token, t_minishell *minishell)
{
	char	*str;

	str = ft_strdup(token->string + *i + 1);
	if (!str)
		exit_perror(minishell, "malloc");
	else if (!*str && token->type == word && token->next
		&& (token->next->type == simple_quote
			|| token->next->type == double_quote))
		return (free(str));
	else if (!*str || *str == ' ' || *str == '/')
		token->string[(*i)++] = '$';
	else if (*str == '$')
		*i += expand_pid(str, token, minishell);
	else if (*str == '?')
		*i += expand_last_status(str, token, minishell);
	else
		*i += expand_env(str, token, minishell);
	free(str);
}

int	expand_string(t_token *token, t_minishell *minishell)
{
	int	i;
	int	expanded;

	i = 0;
	expanded = 0;
	while (token->string[i])
	{
		if (token->string[i] == '$')
		{
			token->string[i] = 0;
			handle_dollard_expansion(&i, token, minishell);
			expanded++;
		}
		i++;
	}
	return (expanded);
}
