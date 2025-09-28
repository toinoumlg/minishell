/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sorted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:45:43 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/28 17:25:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	swap_string(char **array, int i, int j)
{
	char	*tmp;

	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void	print_export_with_quote(char *str)
{
	int	i;
	int	quoted;

	i = 0;
	quoted = 0;
	ft_putstr_fd("export ", 1);
	while (str[i])
	{
		if (str[i] == '=' && !quoted)
		{
			ft_putchar_fd(str[i++], 1);
			ft_putchar_fd('\"', 1);
			quoted++;
		}
		ft_putchar_fd(str[i++], 1);
	}
	ft_putstr_fd("\"\n", 1);
}

void	print_export_sorted(char **envp_sorted)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp_sorted[i])
	{
		if (ft_isalpha(envp_sorted[i][0]))
		{
			tmp = NULL;
			tmp = ft_strchr(envp_sorted[i], '=');
			if (tmp && !*(tmp + 1))
				printf("export %s\"\"\n", envp_sorted[i]);
			else if (tmp)
				print_export_with_quote(envp_sorted[i]);
			else
				printf("export %s\n", envp_sorted[i]);
		}
		i++;
	}
}

void	export_sorted(char **envp)
{
	char	**envp_sorted;
	int		i;
	int		j;

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
	print_export_sorted(envp_sorted);
}
