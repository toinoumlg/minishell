/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <yalaatik@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/09 16:38:56 by yalaatik         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands_redirect_utils.h"
#include "parser/tokens/token_utils.h"
#include "parser/tokens/token_free.h"

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

	new_redirect = set_file(minishell, new_cmd, j);
	append_redirects(&new_cmd->redirects, new_redirect);
}

void	pick_redirects(t_cmd *new_cmd, t_minishell *minishell)
{
	int		j;
	t_token	*tokens;

	tokens = minishell->tokens;
	j = 0;
	while (!is_end_of_command(tokens))
	{
		if (tokens->type == output || tokens->type == append_file
			|| tokens->type == input || tokens->type == here_doc)
		{
			set_redirect(new_cmd, minishell, j);
			return (pick_redirects(new_cmd, minishell));
		}
		j++;
		tokens = tokens->next;
	}
}
