/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:25 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 16:29:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "free.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

void	update_values(t_envp *existing, t_envp *new)
{
	free(existing->line);
	existing->line = new->line;
	free(existing->value);
	existing->value = new->value;
	free(existing->name);
	existing->name = new->name;
	free(new);
}

void	swap_string(char **array, int i, int j)
{
	char	*tmp;

	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void	write_envp_with_quote(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("export ", 1);
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_putchar_fd(str[i++], 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd(str[i++], 1);
	}
	ft_putstr_fd("\"\n", 1);
}

void	sort_envp(char **envp)
{
	char	**envp_sorted;
	int		i;
	int		j;
	char	*tmp;

	envp_sorted = envp;
	i = 0;
	if (!envp_sorted)
		return ;
	while (envp_sorted[i])
	{
		j = i + 1;
		while (envp_sorted[j])
		{
			if (ft_strncmp(envp_sorted[i], envp_sorted[j],
					ft_strlen(envp_sorted[i] + 1)) > 0)
				swap_string(envp_sorted, i, j);
			j++;
		}
		i++;
	}
	i = 0;
	while (envp_sorted[i])
	{
		tmp = NULL;
		tmp = ft_strchr(envp_sorted[i], '=');
		if (tmp && !*(tmp + 1))
			printf("export %s\"\"\n", envp_sorted[i]);
		else if (tmp)
			write_envp_with_quote(envp_sorted[i]);
		else
			printf("export %s\n", envp_sorted[i]);
		i++;
	}
	return ;
}
int	set_name_export(t_envp *new_export, t_minishell *minishell)
{
	char	*name;
	int		i;

	i = -1;
	name = ft_strdup(new_export->line);
	if (!name)
		exit_perror(minishell, "malloc");
	while (name[++i])
	{
		if (name[i] == '=')
		{
			name[i] = 0;
			new_export->name = name;
			return (1);
		}
	}
	new_export->name = name;
	return (0);
}

void	set_value_export(t_envp *new_export, t_minishell *minishell)
{
	char	*value;

	value = NULL;
	if (new_export->contains_sign)
		value = ft_strchr(new_export->line, '=');
	if (value)
	{
		value = ft_strdup(value + 1);
		if (!value)
			exit_perror(minishell, "malloc");
		new_export->value = value;
	}
}

static t_envp	*set_new_export(char *envp_line, t_minishell *minishell)
{
	t_envp	*new_export;

	new_export = malloc(sizeof(t_envp));
	if (!new_export)
		exit_perror(minishell, "malloc");
	memset(new_export, 0, sizeof(t_envp));
	new_export->line = ft_strdup(envp_line);
	if (!new_export->line)
	{
		free(new_export);
		exit_perror(minishell, "malloc");
	}
	new_export->contains_sign = set_name_export(new_export, minishell);
	set_value_export(new_export, minishell);
	return (new_export);
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
	t_envp	*new_export;
	t_envp	*existing;
	int		i;

	status = 0;
	i = 1;
	while (minishell->cmds->args[i])
	{
		if (valid_export(minishell->cmds->args[i]))
		{
			new_export = set_new_export(minishell->cmds->args[i], minishell);
			existing = find_existing_envp(new_export->name, minishell->envp);
			if (existing)
				update_values(existing, new_export);
			else
				append_new_envp(&minishell->envp, new_export);
			if (status != 1)
				status = 0;
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

int	my_export(t_minishell *minishell)
{
	if (!minishell->cmds->args[1])
		return (sort_envp(minishell->envp_array), 0);
	return (export_arguments(minishell));
}
