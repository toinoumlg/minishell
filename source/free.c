/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:46 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/08 19:14:07 by amalangu         ###   ########.fr       */
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

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		if (cmds->args)
			free_array(cmds->args);
		if (cmds->infile)
		{
			free(cmds->infile->path);
			free(cmds->infile);
		}
		if (cmds->outfile)
		{
			free(cmds->outfile->path);
			free(cmds->outfile);
		}
		free(cmds);
		cmds = next;
	}
}
