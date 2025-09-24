/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/23 20:00:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "envp.h"
#include "free.h"
#include "libft.h"
#include <string.h>

static void	update_values(t_envp *existing, char *line, t_minishell *minishell)
{
	free(existing->line);
	free(existing->value);
	free(existing->name);
	existing->line = ft_strdup(line);
	if (!existing->line)
		exit_perror(minishell, "malloc");
	set_name(existing, minishell);
	set_value(existing, minishell);
}

static void	set_new_export(char *line, t_minishell *minishell)
{
	t_envp	*new_export;

	new_export = malloc(sizeof(t_envp));
	if (!new_export)
		exit_perror(minishell, "malloc");
	memset(new_export, 0, sizeof(t_envp));
	append_new_envp(&minishell->envp, new_export);
	new_export->line = ft_strdup(line);
	if (!new_export->line)
		exit_perror(minishell, "malloc");
	set_name(new_export, minishell);
	set_value(new_export, minishell);
	return ;
}

static int	valid_export(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	if (!ft_isalpha(line[i]) && line[i] != '_')
		return (0);
	while (line[i] && line[i] != '=')
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_arguments(t_minishell *minishell)
{
	int		status;
	t_envp	*existing;
	int		i;
	char	*sign;

	status = 0;
	i = 1;
	while (minishell->cmds->args[i])
	{
		if (valid_export(minishell->cmds->args[i]))
		{
			sign = ft_strchr(minishell->cmds->args[i], '=');
			if (sign)
				*sign = 0;
			existing = find_existing_envp(minishell->cmds->args[i],
					minishell->envp);
			if (sign)
				*sign = '=';
			if (existing)
				update_values(existing, minishell->cmds->args[i], minishell);
			else
				set_new_export(minishell->cmds->args[i], minishell);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(minishell->cmds->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		i++;
	}
	return (status);
}

int	ft_export(t_minishell *minishell)
{
	if (!minishell->cmds->args[1])
		return (export_sorted(minishell->envp_array));
	return (export_arguments(minishell));
}
