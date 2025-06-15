/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtsin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:09:26 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/15 18:54:55 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BUILTSIN_H
# define EXEC_BUILTSIN_H

# include "minishell.h"

void	exec_child_builtins(t_pipex *pipex);
void	cd(char *path);

#endif