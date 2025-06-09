/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:46:33 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/08 19:11:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_CHECK_H
# define COMMANDS_CHECK_H

# include "minishell.h"

int	check_for_duplicate(t_token *tokens);
int	check_for_pipe(t_token **tokens);

#endif