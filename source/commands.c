/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:03:22 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/13 18:50:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_args.h"
#include "commands_list.h"
#include "commands_redirect.h"
#include "libft.h"
#include "token_free.h"

static int	add_new_command(t_token **tokens, t_cmd **cmds)
{
	t_cmd	*new;

	new = set_new_command();
	if (!new)
		return (1);
	if (pick_redirects(new, tokens))
		return (1);
	new->args = set_args(tokens);
	if (!new->args)
		return (1);
	new->program_path = ft_strdup(new->args[0]);
	if (!new->program_path)
		return (1);
	free_pipe(tokens);
	append_new_command(cmds, new);
	return (0);
}

int	set_commands(t_token **tokens, t_cmd **cmds)
{
	while (*tokens)
		if (add_new_command(tokens, cmds))
			return (1);
	return (0);
}