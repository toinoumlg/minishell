/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:46:33 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/25 18:57:43 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCESS_H
# define ACCESS_H

# include "minishell.h"

void	set_access(t_file *file);
void	try_access(t_cmd *cmds, char **env);

#endif