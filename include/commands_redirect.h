/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_redirect.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:46:33 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/09 15:58:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_REDIRECT_H
# define COMMANDS_REDIRECT_H

# include "minishell.h"

int	pick_redirects(t_cmd *new, t_token **tokens);

#endif