/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:36:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 16:06:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "exec.h"
#include "free.h"

static void	update_underscore(char *value, t_minishell *minishell)
{
	t_envp	*under_score;

	if (ft_strlen(value) < 1)
		return ;
	under_score = find_existing_envp("_", minishell->envp);
	if (!under_score)
		set_new_envp(ft_strjoin("_=", value), minishell);
	else
	{
		under_score->value = ft_strdup(value);
		if (!under_score->value)
			exit_perror(minishell, "malloc");
		free(under_score->line);
		under_score->line = ft_strjoin("_=", under_score->value);
		if (!under_score->line)
			exit_perror(minishell, "malloc");
	}
}

void	underscore(t_minishell *minishell)
{
	char	**args;
	int		i;

	i = 0;
	args = minishell->cmds->args;
	if (!args)
		return ;
	while (args[i])
		i++;
	if (i == 1)
		update_underscore(minishell->cmds->program->path, minishell);
	else if (i > 1)
		update_underscore(minishell->cmds->args[i - 1], minishell);
}
