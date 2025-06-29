/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:02:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_redirect_utils.h"
#include "token_utils.h"

static void	append_redirects(t_file **redirects, t_file *new_redirect)
{
	t_file	*tmp;
	t_file	*head;

	tmp = *redirects;
	head = *redirects;
	if (!tmp)
	{
		*redirects = new_redirect;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redirect;
	*redirects = head;
}

static int	set_redirect(t_cmd **new, t_token **tokens, int j)
{
	t_file	*new_redirect;
	t_cmd	*tmp;

	tmp = *new;
	new_redirect = set_file(tokens, j);
	if (!new_redirect)
		return (1);
	append_redirects(&tmp->redirects, new_redirect);
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
