/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/04 18:32:39 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strncmp.h"
#include "parse_read_line.h"
#include "split.h"
#include <string.h>
#include <readline/readline.h>

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
	}
	return (0);
}
