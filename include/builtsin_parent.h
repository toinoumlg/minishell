/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin_parent.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:48:13 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 18:57:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTSIN_PARENT_H
# define BUILTSIN_PARENT_H

# include "minishell.h"

void	exec_builtin_in_parent(t_pipex *pipex, char **env);

#endif