/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:41:45 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/22 20:05:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_ENVP_H
# define INIT_ENVP_H

# include "minishell.h"

void	set_envp(t_minishell *minishell, char **envp);

char	*set_name(t_envp *new, t_minishell *minishell);
char	*set_value(t_envp *new, t_minishell *minishell);
void	append_new_envp(t_envp **envp_struct, t_envp *new_envp);
t_envp	*find_existing_envp(char *name, t_envp *envp);

#endif