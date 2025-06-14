/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:46:33 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/10 17:07:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_LIST_H
# define COMMANDS_LIST_H

# include "minishell.h"

t_cmd	*set_new_command(void);
void	append_new_command(t_cmd **cmds, t_cmd *new);

#endif