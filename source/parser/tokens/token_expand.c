/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 15:38:50 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_expand_utils.h"
#include "token_free.h"
#include <stdio.h>
#include <stdlib.h>

// static void	expand_last_status(t_minishell *minishell, int *i, char **out)
// {
// 	char	*value;

// 	value = ft_itoa(minishell->last_status);
// 	if (value && strjoin_inplace(out, value))
// 	{
// 		free(value);
// 		exit_perror(minishell, "malloc ");
// 	}
// 	free(value);
// 	(*i)++;
// }

// static void	expand_env(int *i, t_minishell *minishell, char *str,
// char **out)
// {
// 	int		j;
// 	t_envp	*value;
// 	char	saved;

// 	j = *i;
// 	while (str[j] && is_var_char(str[j]))
// 		j++;
// 	saved = str[j];
// 	str[j] = 0;
// 	value = find_existing_envp(str + *i, minishell->envp);
// 	if (value && strjoin_inplace(out, value->value))
// 	{
// 		exit_perror(minishell, "malloc");
// 	}
// 	str[j] = saved;
// 	*i = j;
// }

// void	handle_expand(int *i, char *str, char **out, t_minishell *minishell)
// {
// 	(*i)++;
// 	if (!str[*i])
// 	{
// 		if ((ft_strlen(*out) && ft_strlen("$")) && strjoin_inplace(out, "$"))
// 			exit_perror(minishell, "malloc ");
// 	}
// 	else if (str[*i] == '?')
// 		expand_last_status(minishell, i, out);
// 	else if (is_var_start(str[*i]))
// 		expand_env(i, minishell, str, out);
// 	else if (!is_var_char(str[*i]))
// 		if ((ft_strlen(*out) && ft_strlen("$")) && strjoin_inplace(out, "$"))
// 			exit_perror(minishell, "malloc ");
// }

// static void	expand_token_inline(t_token *token, t_minishell *minishell)
// {
// 	char	*str;
// 	char	*out;
// 	int		i;
// 	char	buf[2];

// 	str = token->string;
// 	out = NULL;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			handle_expand(&i, str, &out, minishell);
// 		if (!str[i])
// 			break ;
// 		buf[0] = str[i];
// 		buf[1] = '\0';
// 		if (strjoin_inplace(&out, buf))
// 			exit_perror(minishell, "malloc ");
// 		i++;
// 	}
// 	free(token->string);
// 	token->string = out;
// }

// static char	*env_lookup_dup(const char *name, t_minishell *m)
// {
// 	t_envp	*e;
// 	size_t	nlen;

// 	e = m->envp;
// 	nlen = ft_strlen(name);
// 	while (e)
// 	{
// 		if (e->name && ft_strncmp(e->name, name, nlen) == 0
// 			&& e->name[nlen] == '\0')
// 		{
// 			if (e->value)
// 				return (ft_strdup(e->value));
// 			return (ft_strdup(""));
// 		}
// 		e = e->next;
// 	}
// 	return (ft_strdup(""));
// }

// static void	strjoin_inplace(char **dst, const char *src)
// {
// 	char	*tmp;

// 	tmp = *dst;
// 	if (src)
// 		*dst = ft_strjoin(*dst, src);
// 	else
// 		*dst = ft_strjoin(*dst, "");
// 	free(tmp);
// }

// static void	expand_token_inline(t_token *t, t_minishell *m)
// {
// 	char	*s;
// 	char	*out;
// 	int		i;
// 	int		j;
// 	char	saved;
// 	char	*val;
// 	char	buf[2];

// 	s = t->string;
// 	out = ft_strdup("");
// 	i = 0;
// 	j = 0;
// 	saved = 0;
// 	val = NULL;
// 	buf[0] = 0;
// 	buf[1] = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			i++;
// 			if (!s[i])
// 			{
// 				strjoin_inplace(&out, "$");
// 				break ;
// 			}
// 			if (s[i] == '?')
// 			{
// 				val = ft_itoa(m->last_status);
// 				strjoin_inplace(&out, val);
// 				free(val);
// 				i++;
// 				continue ;
// 			}
// 			if (is_var_start(s[i]))
// 			{
// 				j = i;
// 				while (s[j] && is_var_char(s[j]))
// 					j++;
// 				saved = s[j];
// 				s[j] = '\0';
// 				val = env_lookup_dup(&s[i], m);
// 				strjoin_inplace(&out, val);
// 				if (val)
// 					free(val);
// 				s[j] = saved;
// 				i = j;
// 				continue ;
// 			}
// 			strjoin_inplace(&out, "$");
// 			continue ;
// 		}
// 		buf[0] = s[i];
// 		buf[1] = '\0';
// 		strjoin_inplace(&out, buf);
// 		i++;
// 	}
// 	free(t->string);
// 	t->string = out;
// }

void	expand_last_value(char *str, t_token *token, t_minishell *minishell)
{
	char	*nbr_str;
	char	*tmp;

	nbr_str = ft_itoa(minishell->last_status);
	tmp = token->string;
	token->string = ft_strjoin(tmp, nbr_str);
	free(nbr_str);
	free(tmp);
	str++;
	tmp = token->string;
	token->string = ft_strjoin(tmp, str);
	free(tmp);
}

void	expand_env(char *str, t_token *token, t_minishell *minishell)
{
	t_envp	*expand;
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	str[i] = 0;
	expand = find_existing_envp(str, minishell->envp);
	if (expand)
	{
		tmp = token->string;
		token->string = ft_strjoin(tmp, expand->value);
		free(tmp);
		tmp = token->string;
		token->string = ft_strjoin(tmp, str + i + 1);
		free(tmp);
	}
}

void	expand_pid(void)
{
}

void	expand(int i, t_token *token, t_minishell *minishell)
{
	char	*str;

	str = ft_strdup(token->string + i + 1);
	token->string[i] = 0;
	if (!str)
		exit_perror(minishell, "malloc");
	else if (!*str && token->next && (token->next->type == simple_quote
			|| token->next->type == double_quote))
		;
	else if (!*str)
		token->string[i] = '$';
	else if (*str == '$')
		expand_pid();
	else if (*str == '?')
		expand_last_value(str, token, minishell);
	else
		expand_env(str, token, minishell);
	if (str)
		free(str);
}

void	try_expand(t_token *token, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (token->string[i])
	{
		if (token->string[i] == '$')
			expand(i, token, minishell);
		i++;
	}
}

void	expand_tokens(t_minishell *minishell)
{
	t_token	*tokens;

	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == word || tokens->type == double_quote)
			try_expand(tokens, minishell);
		tokens = tokens->next;
	}
}
