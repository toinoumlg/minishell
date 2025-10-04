/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/10/04 14:29:27 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtsin.h"
#include "envp.h"
#include "free.h"
#include "libft.h"
#include <string.h>

static void	update_values(t_envp *existing, char *line, t_minishell *minishell)
{
	if (!ft_strchr(line, '='))
		return ;
	free(existing->line);
	existing->line = ft_strdup(line);
	if (!existing->line)
		exit_perror(minishell, "malloc");
	free(existing->name);
	set_name(existing, minishell);
	if (existing->value)
		free(existing->value);
	set_value(existing, minishell);
}

static void	add_export(char *line, t_minishell *minishell)
{
	t_envp	*new_export;

	new_export = malloc(sizeof(t_envp));
	if (!new_export)
		exit_perror(minishell, "malloc");
	ft_memset(new_export, 0, sizeof(t_envp));
	append_new_envp(&minishell->envp, new_export);
	new_export->line = ft_strdup(line);
	if (!new_export->line)
		exit_perror(minishell, "malloc");
	set_name(new_export, minishell);
	set_value(new_export, minishell);
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

void	export_arguments(char *export, t_minishell *minishell)
{
	t_envp	*existing;
	char	*sign;

	sign = ft_strchr(export, '=');
	if (sign)
		*sign = 0;
	existing = find_existing_envp(export, minishell->envp);
	if (sign)
		*sign = '=';
	if (existing)
		update_values(existing, export, minishell);
	else
		add_export(export, minishell);
}

int	ft_export(t_minishell *minishell)
{
	int	status;
	int	i;

	if (!minishell->cmds->args[1])
		return (export_sorted(minishell->envp_array), 0);
	status = 0;
	i = 1;
	while (minishell->cmds->args[i])
	{
		if (valid_export(minishell->cmds->args[i]))
			export_arguments(minishell->cmds->args[i], minishell);
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
