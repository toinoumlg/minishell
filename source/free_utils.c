/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:01:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:07:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_array(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->string)
			free(tokens->string);
		free(tokens);
		tokens = next;
	}
}

void	free_file(t_file *file)
{
	t_file	*next;

	while (file)
	{
		next = file->next;
		if (file->path)
			free(file->path);
		free(file);
		file = next;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_array(cmds->args);
		free_file(cmds->program);
		free_file(cmds->redirects);
		free(cmds);
		cmds = next;
	}
}
