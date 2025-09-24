/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:44:58 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/24 18:38:15 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTSIN_H
# define BUILTSIN_H

# ifndef BUILTSIN_CMDS
#  define ECHO "echo"
#  define ENV "env"
#  define PWD "pwd"
#  define CD "cd"
#  define EXIT "exit"
#  define EXPORT "export"
#  define UNSET "unset"
# endif

# include "free.h"
# include "libft.h"
# include "minishell.h"

int		is_a_builtin(char *str);
void	exec_builtsin_in_child(t_minishell *minishell);
void	exec_builtsin_in_parent(t_minishell *minishell);

int		echo(t_minishell *minishell);
int		env(t_minishell *minishell);
int		pwd(t_minishell *minishell);

void	update_pwd(t_minishell *minishell);
int		cd(t_minishell *minishell);
int		ft_exit(t_minishell *minishell);
int		ft_export(t_minishell *minishell);
void	export_sorted(char **envp);
int		unset(t_minishell *minishell);

#endif