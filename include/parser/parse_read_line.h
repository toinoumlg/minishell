/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:10:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/29 15:49:12 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_READ_LINE_H
# define PARSE_READ_LINE_H

# include "commands.h"
# include "free.h"
# include "minishell.h"
# include "token.h"
# include <readline/history.h>

void	parse_read_line(t_minishell *minishell);

// pre parsing
void	set_paths(t_minishell *minishell);
void	set_envp_array(t_minishell *minishell);

// post parsing
void	*alloc_pipe_fds(t_minishell *minishell);
void	*alloc_pids(t_minishell *minishell);
int		set_size(t_cmd *cmds);

#endif