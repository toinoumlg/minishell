/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/12 20:51:40 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum s_enum_token
{
	word,
	is_pipe,
	input,
	output,
	here_doc,
	append_file,
	double_quote,
	simple_quote
}					t_enum_token;

typedef struct s_file
{
	char			*path;
	t_enum_token	type;
	int				fd;
	int				is_dir;
	int				exist;
	int				read;
	int				write;
	int				exec;
}					t_file;

typedef struct s_cmd
{
	char			*program_path;
	char			**args;
	t_file			*infile;
	t_file			*outfile;
	int				here_doc;
	int				append_file;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*string;
	t_enum_token	type;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	t_cmd			*cmds;
	int (*pipe_fds)[2];
	int				*pids;
}					t_minishell;

#endif
