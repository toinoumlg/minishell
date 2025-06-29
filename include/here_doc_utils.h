/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:10:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:19:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_UTILS_H
# define HERE_DOC_UTILS_H

# include "minishell.h"

void	close_here_doc(int here_doc_pipe[2], t_file *here_doc_file,
			t_pipex *pipex);

#endif