/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 18:55:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_free.h"
#include "token_utils.h"
#include <stdlib.h>
#include <string.h>

static t_token	*get_operator_token(t_token **tokens, int j)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *tokens;
	while (i++ < j && tmp)
		tmp = tmp->next;
	return (tmp);
}

static t_file	*new_file(void)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_file));
	return (new);
}

static t_file	*set_file(t_token **tokens, int j)
{
	t_file	*new;
	t_token	*tmp;

	tmp = *tokens;
	new = new_file();
	if (!new)
		return (NULL);
	tmp = get_operator_token(tokens, j);
	new->path = ft_strdup(tmp->next->string);
	if (!new->path)
		return (free(new), NULL);
	new->type = tmp->type;
	new->next = NULL;
	free_i_token(tokens, j);
	free_i_token(tokens, j);
	return (new);
}

void	append_file_to_cmd(t_cmd **new, t_file *new_redirect)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = *new;
	head = tmp;
	if (!tmp->redirect)
	{
		tmp->redirect = new_redirect;
		tmp = *new;
		return ;
	}
	while (tmp->redirect->next)
		tmp->redirect = tmp->redirect->next;
	tmp->redirect->next = new_redirect;
	*new = head;
}

int	set_redirect(t_cmd **new, t_token **tokens, int j)
{
	t_file	*new_redirect;

	new_redirect = set_file(tokens, j);
	if (!new_redirect)
		return (1);
	append_file_to_cmd(new, new_redirect);
	return (0);
}

int	pick_redirects(t_cmd **new, t_token **tokens)
{
	int		j;
	t_token	*tmp;

	tmp = *tokens;
	j = 0;
	while (!is_end_of_command(tmp))
	{
		if (tmp->type == output || tmp->type == append_file
			|| tmp->type == input || tmp->type == here_doc)
		{
			if (!set_redirect(new, tokens, j))
				return (pick_redirects(new, tokens));
			else
				return (1);
		}
		j++;
		tmp = tmp->next;
	}
	return (0);
}
