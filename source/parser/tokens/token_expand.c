/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 08:38:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	strjoin_inplace(char **dst, const char *src)
{
	char	*tmp;

	tmp = *dst;
	if (src)
		*dst = ft_strjoin(*dst, src);
	else
		*dst = ft_strjoin(*dst, "");
	free(tmp);
}

static void	expand_token_inline(t_token *t, t_minishell *m)
{
	char	*s;
	char	*out;
	int		i;
	int		j;
	char	saved;
	char	*val;
	char	buf[2];

	s = t->string;
	out = ft_strdup("");
	i = 0;
	j = 0;
	saved = 0;
	val = NULL;
	buf[0] = 0;
	buf[1] = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (!s[i])
			{
				strjoin_inplace(&out, "$");
				break ;
			}
			if (s[i] == '?')
			{
				val = ft_itoa(m->last_status);
				strjoin_inplace(&out, val);
				free(val);
				i++;
				continue ;
			}
			if (is_var_start(s[i]))
			{
				j = i;
				while (s[j] && is_var_char(s[j]))
					j++;
				saved = s[j];
				s[j] = '\0';
				val = env_lookup_dup(&s[i], m);
				strjoin_inplace(&out, val);
				if (val)
					free(val);
				s[j] = saved;
				i = j;
				continue ;
			}
			strjoin_inplace(&out, "$");
			continue ;
		}
		buf[0] = s[i];
		buf[1] = '\0';
		strjoin_inplace(&out, buf);
		i++;
	}
	free(t->string);
	t->string = out;
}

t_token	*free_empty_tokens(t_token *tokens)
{
	t_token	*head;
	int		i;

	head = tokens;
	i = 0;
	while (tokens)
	{
		if (!ft_strlen(tokens->string))
			free_i_token(&head, i);
		i++;
		tokens = tokens->next;
	}
	return (head);
}

void	expand_tokens(t_minishell *m)
{
	t_token	*t;

	t = m->tokens;
	while (t)
	{
		if (t->type == word || t->type == double_quote)
			expand_token_inline(t, m);
		t = t->next;
	}
	// m->tokens = free_empty_tokens(m->tokens);
}
