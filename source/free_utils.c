/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:01:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 19:14:06 by amalangu         ###   ########.fr       */
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
	if (file)
	{
		if (file->path)
			free(file->path);
		free(file);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	free_file(cmd->program);
	free_file(cmd->infile);
	free_file(cmd->outfile);
	free(cmd);
}