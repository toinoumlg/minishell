/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:01:50 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 19:41:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_array(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			ft_free(args[i++]);
		ft_free(args);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->string)
			ft_free(tokens->string);
		ft_free(tokens);
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
			ft_free(file->path);
		ft_free(file);
		file = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	free_file(cmd->program);
	free_file(cmd->redirects);
	ft_free(cmd);
}
