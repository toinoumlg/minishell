/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 16:10:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include "parse_read_line.h"
#include "set_env.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

void	exec(t_minishell *minishell)
{
	print_commands(minishell->cmds);
}

int	is_exit(t_cmd *cmds)
{
	if (cmds && cmds->args && !ft_strncmp(cmds->args[0], "exit", 4))
		return (printf("exit\n"), free_cmds(cmds), 1);
	else
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*read_line;
	char		**env;
	t_minishell	minishell;

	memset(&minishell, 0, sizeof(t_minishell));
	env = set_env(envp);
	if (!env)
		return (1);
	while (argc && argv)
	{
		read_line = readline("minishell >> ");
		parse_read_line(read_line, &minishell, env);
		if (is_exit(minishell.cmds))
			return (0);
		exec(&minishell);
		free_cmds(minishell.cmds);
		memset(&minishell, 0, sizeof(t_minishell));
	}
	return (0);
}
