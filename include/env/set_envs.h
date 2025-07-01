/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:02:27 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 18:45:36 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ENVS_H
# define SET_ENVS_H

# include "minishell.h"

char	**set_envs(t_minishell *minishell, char **envp);

#endif