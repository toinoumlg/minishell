/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/10/01 18:23:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "parser/commands.h"
#include "parser/token.h"
#include <string.h>

static t_file	*new_file(t_minishell *minishell)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		exit_perror(minishell, "malloc ");
	ft_memset(new, 0, sizeof(t_file));
	return (new);
}

static void	append_redirects(t_file **redirects, t_file *new_redirect)
{
	t_file	*tmp;

	tmp = *redirects;
	if (!tmp)
	{
		*redirects = new_redirect;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redirect;
}

static void	set_redirect(t_cmd *new_cmd, t_minishell *minishell,
		t_token **redirect_add)
{
	t_file	*new_redirect;
	t_token	*redirect;

	redirect = *redirect_add;
	new_redirect = new_file(minishell);
	append_redirects(&new_cmd->redirects, new_redirect);
	new_redirect->path = ft_strdup(redirect->next->string);
	new_redirect->fd = -1;
	if (!new_redirect->path)
		exit_perror(minishell, "malloc ");
	if (redirect->type == here_doc)
	{
		if (redirect->next->type == word)
			new_redirect->type = here_doc_word;
		else
			new_redirect->type = here_doc_quote;
	}
	else
		new_redirect->type = redirect->type;
	remove_token(&minishell->tokens, redirect_add);
	remove_token(&minishell->tokens, redirect_add);
}

void	pick_redirects(t_cmd *new_cmd, t_minishell *minishell)
{
	t_token	*tokens;

	tokens = minishell->tokens;
	while (!is_end_of_command(tokens))
	{
		if (is_a_redirect(tokens->type))
			set_redirect(new_cmd, minishell, &tokens);
		else
			tokens = tokens->next;
	}
}
