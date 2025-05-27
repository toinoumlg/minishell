/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/05/27 15:05:16 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strncmp.h"
#include "minishell.h"
#include "split.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	exec(void)
{
}

void	parse_read_line(char *read_line, t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->split = split(read_line, ' ');
	while (minishell->split[i])
		printf("%s\n", minishell->split[i++]);
	free(read_line);
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
		if (!ft_strncmp(minishell.split[0], "exit", 4))
			break ;
		exec();
		free_split(minishell.split);
	}
	free_split(minishell.split);
	return (0);
}
