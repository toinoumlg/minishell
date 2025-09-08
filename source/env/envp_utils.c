/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:58:49 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/08 13:52:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// Return a pointer to envp struct that match specified name.
// Return NULL if not in environnement.
t_envp	*find_existing_envp(char *name, t_envp *envp)
{
	int	i;

	i = 0;
	if (!envp || !name)
		return (NULL);
	while (envp)
	{
		if (!ft_strncmp(name, envp->name, ft_strlen(name) + 1))
			return (envp);
		i++;
		envp = envp->next;
	}
	return (NULL);
}
