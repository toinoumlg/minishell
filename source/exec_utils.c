/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:15:21 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 16:40:54 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_builtin_to_exec_in_parent(char *cmd)
{
	return (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "exit", 5));
}

int	is_child_executable(t_cmd *cmd)
{
	return ((!cmd->infile || !cmd->infile->read)) && (!cmd->outfile
		|| !cmd->outfile->write) && (!cmd->append_file
		|| !cmd->append_file->write);
}
