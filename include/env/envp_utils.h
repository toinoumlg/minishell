/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:08:12 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/10 08:29:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_UTILS_H
# define ENVP_UTILS_H

# include "minishell.h"

char	*set_name(char *line, t_minishell *minishell);
char	*set_value(char *line, t_minishell *minishell);
t_envp	*set_new_envp(char *line, t_minishell *minishell);
void	append_new_envp(t_envp **envp_struct, t_envp *new_envp);
t_envp	*find_existing_envp(char *name, t_envp *envp);

#endif