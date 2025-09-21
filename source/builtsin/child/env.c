/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 16:06:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <stdlib.h>

int	env(t_minishell *minishell)
{
	t_envp	*envp;

	envp = minishell->envp;
	while (envp)
	{
		ft_putstr_fd(envp->line, 1);
		ft_putstr_fd("\n", 1);
		envp = envp->next;
	}
	return (0);
}
