/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:28:23 by amalangu          #+#    #+#             */
/*   Updated: 2025/07/03 21:10:05 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <string.h>

void	add_string_to_token(char *start, int i, t_token *new_token,
		t_minishell *minishell)
{
	new_token->string = ft_strdup(start);
	if (!new_token->string)
	{
		free(new_token);
		exit(free_on_exit_error(minishell));
	}
	new_token->string[i] = 0;
}

t_token	*set_new_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(free_on_exit_error(minishell));
	memset(new_token, 0, sizeof(t_token));
	return (new_token);
}

void	append_new_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;
	t_token	*head;
	int		i;

	i = 0;
	tmp = *tokens;
	head = tmp;
	if (!tmp)
	{
		*tokens = new_token;
		return ;
	}
	while (tmp->next && ++i)
		tmp = tmp->next;
	++i;
	tmp->next = new_token;
	*tokens = head;
}
