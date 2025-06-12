/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:15:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/12 17:25:13 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_free.h"
#include "token_utils.h"
#include <stdlib.h>
#include <string.h>

static char	*get_file_path(t_token **tokens, int j)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *tokens;
	while (i++ < j + 1)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp->string));
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
	new->path = get_file_path(tokens, j);
	if (!new->path)
		return (free(new), NULL);
	new->type = tmp->type;
	free_i_token(tokens, j);
	free_i_token(tokens, j);
	return (new);
}

int	pick_redirects(t_cmd *new, t_token **tokens)
{
	int		j;
	t_token	*tmp;

	tmp = *tokens;
	j = 0;
	while (!is_end_of_command(tmp))
	{
		if (tmp->type == output || tmp->type == append_file)
		{
			new->outfile = set_file(tokens, j);
			if (!new->outfile)
				return (1);
			pick_redirects(new, tokens);
		}
		if (tmp->type == input || tmp->type == here_doc)
		{
			new->infile = set_file(tokens, j);
			if (!new->infile)
				return (1);
			pick_redirects(new, tokens);
		}
		j++;
		tmp = tmp->next;
	}
	return (0);
}
