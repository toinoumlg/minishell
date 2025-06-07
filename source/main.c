/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 16:53:10 by amalangu         ###   ########.fr       */
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
		memset(&minishell, 0, sizeof(t_minishell));
	}
	return (0);
}
