/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/08 11:04:52 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_READ_LINE_H
# define PARSE_READ_LINE_H

# include "minishell.h"

void	parse_read_line(char *read_line, t_minishell *minishell, char **env);

#endif