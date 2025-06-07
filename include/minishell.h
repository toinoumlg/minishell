/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/05 16:38:20 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_file
{
	char			*path;
	int				fd;
	int				exist;
	int				read;
	int				write;
	int				exec;
}					t_file;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	t_file			*infile;
	t_file			*outfile;
	int				here_doc;
	int				append_file;
	int				pipe_to_next;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*word;
	int				is_operator;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	t_cmd			*cmds;
	t_token			*tokens;
	int				parse_error;
	int				exit;
}					t_minishell;

#endif
