/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:04:56 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 19:50:11 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "minishell.h"

void	pick_redirects(t_cmd *new_cmd, t_minishell *minishell);
void	set_args(t_cmd *new_cmd, t_minishell *minishell);
void	set_commands(t_minishell *minishell);

#endif
