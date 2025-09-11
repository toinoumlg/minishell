/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 17:38:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_expand_utils.h"
#include "token_free.h"
#include <stdlib.h>

static void	expand_last_status(t_minishell *minishell, int *i, char **out)
{
	char	*value;

	value = ft_itoa(minishell->last_status);
	if (strjoin_inplace(out, value))
	{
		free(value);
		exit_perror(minishell, "malloc ");
	}
	free(value);
	(*i)++;
}

static void	expand_env(int *i, t_minishell *minishell, char *str, char **out)
{
	int		j;
	t_envp	*value;
	char	saved;

	j = *i;
	while (str[j] && is_var_char(str[j]))
		j++;
	saved = str[j];
	str[j] = 0;
	value = find_existing_envp(str + *i, minishell->envp);
	if (value && strjoin_inplace(out, value->value))
		exit_perror(minishell, "malloc");
	str[j] = saved;
	*i = j;
}

void	handle_expand(int *i, char *str, char **out, t_minishell *minishell)
{
	(*i)++;
	if (!str[*i])
	{
		if (strjoin_inplace(out, "$"))
			exit_perror(minishell, "malloc ");
	}
	else if (str[*i] == '?')
		expand_last_status(minishell, i, out);
	else if (is_var_start(str[*i]))
		expand_env(i, minishell, str, out);
	else if (!is_var_char(str[*i]))
		if (strjoin_inplace(out, "$"))
			exit_perror(minishell, "malloc ");
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
		if (strjoin_inplace(&out, buf))
			exit_perror(minishell, "malloc ");
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
