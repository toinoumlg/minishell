/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 17:07:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_free.h"
#include <stdlib.h>

/* ---- lookup env: renvoie une DUP de la valeur ou "" si absente ---- */
static char	*env_lookup_dup(const char *name, t_minishell *m)
{
	t_envp	*e;
	size_t	nlen;

	e = m->envp;
	nlen = ft_strlen(name);
	while (e)
	{
		if (e->name && ft_strncmp(e->name, name, nlen) == 0
			&& e->name[nlen] == '\0')
		{
			if (e->value)
				return (ft_strdup(e->value));
			return (ft_strdup(""));
		}
		e = e->next;
	}
	return (ft_strdup(""));
}

/* petits helpers locaux */
static int	is_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

static int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	return (0);
}

static void	strjoin_inplace(char **dst, const char *src, t_minishell *minishell)
{
	char	*tmp;

	tmp = *dst;
	if (!*dst && src)
	{
		*dst = ft_strdup(src);
		if (!*dst)
			exit_perror(minishell, "malloc ");
	}
	else if (*dst && src)
	{
		*dst = ft_strjoin(tmp, src);
		if (!*dst)
			exit_perror(minishell, "malloc ");
	}
	free(tmp);
}

static void	expand_last_status(t_minishell *minishell, int *i, char **out)
{
	char	*value;

	value = ft_itoa(minishell->last_status);
	strjoin_inplace(out, value, minishell);
	free(value);
	(*i)++;
}

static void	expand_env(int *i, t_minishell *minishell, char *str, char **out)
{
	int		j;
	char	*value;
	char	saved;

	j = *i;
	while (str[j] && is_var_char(str[j]))
		j++;
	saved = str[j];
	str[j] = 0;
	
	value = env_lookup_dup(str + *i, minishell);
	strjoin_inplace(out, value, minishell);
	if (value)
		free(value);
	str[j] = saved;
	*i = j;
}

void	handle_expand(int *i, char *str, char **out, t_minishell *minishell)
{
	(*i)++;
	if (!str[*i])
		strjoin_inplace(out, "$", minishell);
	else if (str[*i] == '?')
		expand_last_status(minishell, i, out);
	else if (is_var_start(str[*i]))
		expand_env(i, minishell, str, out);
	else if (!is_var_char(str[*i]))
		strjoin_inplace(out, "$", minishell);
}

static void	expand_token_inline(t_token *token, t_minishell *minishell)
{
	char	*str;
	char	*out;
	int		i;
	char	buf[2];

	str = token->string;
	out = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			handle_expand(&i, str, &out, minishell);
		buf[0] = str[i];
		buf[1] = '\0';
		strjoin_inplace(&out, buf, minishell);
		i++;
	}
	free(token->string);
	token->string = out;
}

void	expand_tokens(t_minishell *minishell)
{
	t_token	*tokens;

	tokens = minishell->tokens;
	if (minishell->read_line)
	{
		free(minishell->read_line);
		minishell->read_line = NULL;
	}
	while (tokens)
	{
		if (tokens->type == word || tokens->type == double_quote)
			expand_token_inline(tokens, minishell);
		tokens = tokens->next;
	}
}
