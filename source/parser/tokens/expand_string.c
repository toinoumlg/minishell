/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:56:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 14:52:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "parser/token.h"

static int	expand_last_status(char *str, t_token *token,
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

static void	append_env_to_string(char *str, t_token *token,
		t_minishell *minishell, t_envp *expand)
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
	token->string = ft_strjoin(tmp, str);
	if (!token->string)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	free(tmp);
}

static int	expand_env(char *str, t_token *token, t_minishell *minishell)
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
	if (!expand || !expand->value)
	{
		tmp = token->string;
		token->string = ft_strjoin(tmp, str + i);
		free(tmp);
		return (-1);
	}
	append_env_to_string(str + i, token, minishell, expand);
	return (ft_strlen(expand->value) - 1);
}

/*	Handle variable expansion for different '$' cases:
	Empty after '$': skip if followed by quotes, ortherwise restore '$'
	'$$': expands process ID, '$?': expands to last exit status
	Other cases: attempts enviroment variable expansion	*/
void	handle_expansion(int *i, t_token *token, t_minishell *minishell)
{
	char	*str;

	str = ft_strdup(token->string + *i + 1);
	if (!str)
		exit_perror(minishell, "malloc");
	else if (!*str && token->type == word && token->next
		&& (token->next->type == simple_quote
			|| token->next->type == double_quote))
		return (free(str));
	else if (!*str || *str == '$' || *str == ' ' || *str == '/')
		token->string[(*i)++] = '$';
	else if (*str == '?')
		*i += expand_last_status(str, token, minishell);
	else
		*i += expand_env(str, token, minishell);
	free(str);
}
