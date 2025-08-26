/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:08:12 by amalangu          #+#    #+#             */
/*   Updated: 2025/08/26 17:09:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_UTILS_H
# define ENVP_UTILS_H

# include "minishell.h"

t_envp	*find_existing_envp(char *name, t_envp *envp);

#endif