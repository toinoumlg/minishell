/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/21 07:35:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_redirect_utils.h"
#include "free.h"
#include "token_free.h"
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

static void	set_redirect(t_cmd *new_cmd, t_minishell *minishell, int j)
{
	t_file	*new_redirect;

	new_redirect = set_file(minishell, j);
	append_redirects(&new_cmd->redirects, new_redirect);
}

int	is_a_file(t_enum_token type)
{
	return (type == output || type == append_file || type == input
		|| type == here_doc);
}

void	pick_redirects(t_cmd *new_cmd, t_minishell *minishell)
{
	int		j;
	t_token	*tokens;

	tokens = minishell->tokens;
	j = 0;
	while (!is_end_of_command(tokens))
	{
		if (is_a_file(tokens->type))
			return (set_redirect(new_cmd, minishell, j), pick_redirects(new_cmd,
					minishell));
		j++;
		tokens = tokens->next;
	}
}
