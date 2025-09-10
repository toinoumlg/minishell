/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 06:53:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "token_free.h"
#include "parser/tokens/token_utils.h"
#include <stdlib.h>
#include <string.h>

static t_token	*get_operator_token(t_token *tokens, int j)
{
	int	i;

	i = 0;
	while (i++ < j && tokens)
		tokens = tokens->next;
	return (tokens);
}

static t_file	*new_file(t_minishell *minishell, t_cmd *new_cmd)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
	{
		free(new_cmd);
		exit(free_minishell(minishell));
	}
	memset(new, 0, sizeof(t_file));
	return (new);
}

t_file	*set_file(t_minishell *minishell, t_cmd *new_cmd, int j)
{
	t_file	*new;
	t_token	*tmp;

	new = new_file(minishell, new_cmd);
	tmp = get_operator_token(minishell->tokens, j);
	new->path = ft_strdup(tmp->next->string);
	if (!new->path)
	{
		free(new);
		free_cmds(new_cmd);
		exit(free_minishell(minishell));
	}
	new->type = tmp->type;
	free_i_token(&minishell->tokens, j);
	free_i_token(&minishell->tokens, j);
	return (new);
}
