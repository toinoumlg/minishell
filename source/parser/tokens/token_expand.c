/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:14:42 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/20 15:02:54 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "token_free.h"
#include <string.h>

static char	*value_for_name(char *name, t_envp *envp)
{
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

static void	expand_last_status(t_token *tokens, t_minishell *minishell)
{
	char	*tmp;

	tmp = ft_itoa(minishell->last_status);
	if (!tmp)
		exit(free_on_exit_error(minishell));
	tokens->string = ft_strdup(tmp);
	free(tmp);
	if (!tokens->string)
		exit(free_on_exit_error(minishell));
}

static int	index_in_envp(char *name, t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (i);
		i++;
		envp = envp->next;
	}
	return (-1);
}

static void	expand_from_envp(t_token *tokens, t_minishell *minishell, int i)
{
	char	*tmp;

	tmp = tokens->string;
	if (!tmp)
		exit(free_on_exit_error(minishell));
	if (index_in_envp(tmp + 1, minishell->envp) < 0)
		return (free_i_token(&minishell->tokens, i));
	tokens->string = value_for_name(tmp + 1, minishell->envp);
	free(tmp);
	if (!tokens->string)
		exit(free_on_exit_error(minishell));
}

void	expand_tokens(t_minishell *minishell)
{
	t_token	*tokens;
	int		i;

	tokens = minishell->tokens;
	i = 0;
	while (tokens)
	{
		if (tokens->type == word || tokens->type == double_quote)
		{
			if (ft_strchr(tokens->string, '$'))
			{
				if (strcmp(tokens->string, "$?") == 0)
					expand_last_status(tokens, minishell);
				else
					expand_from_envp(tokens, minishell, i);
			}
		}
		i++;
		tokens = tokens->next;
	}
}
