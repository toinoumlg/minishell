/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 16:02:01 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_read_line.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

void	exec(t_minishell *minishell)
{
	(void)minishell;
}

void	free_minishell(t_minishell minishell)
{
	t_token	*tmp;

	while (minishell.tokens)
	{
		tmp = minishell.tokens->next;
		free(minishell.tokens);
		minishell.tokens = tmp;
	}
	memset(&minishell, 0, sizeof(t_minishell));
}

int	main(void)
{
	char		*read_line;
	t_minishell	minishell;

	memset(&minishell, 0, sizeof(t_minishell));
	while (1)
	{
		read_line = readline("minishell >> ");
		parse_read_line(read_line, &minishell);
		exec(&minishell);
		free_minishell(minishell);
	}
	return (0);
}
