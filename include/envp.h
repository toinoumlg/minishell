/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:41:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 15:05:26 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

# ifndef ENVP_VAR
#  define PATH "PATH"
#  define _PWD "PWD"
#  define OLDPWD "OLDPWD"
# endif

void	set_envp(t_minishell *minishell, char **envp);
void	set_new_envp(char *line, t_minishell *minishell);

// utils
char	*set_name(t_envp *new, t_minishell *minishell);
char	*set_value(t_envp *new, t_minishell *minishell);
void	append_new_envp(t_envp **envp_struct, t_envp *new_envp);
t_envp	*find_existing_envp(char *name, t_envp *envp);

#endif