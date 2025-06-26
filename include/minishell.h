/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/26 16:33:51 by amalangu         ###   ########.fr       */
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
	struct s_file	*next;
}					t_file;

typedef struct s_cmd
{
	t_file			*program;
	char			**args;
	t_file			*infile;
	t_file			*outfile;
	t_file			*here_doc;
	t_file			*append_file;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*string;
	t_enum_token	type;
	struct s_token	*next;
}					t_token;

typedef struct s_pipex
{
	t_cmd			*cmds;
	int				i;
	int				size;
	int (*pipe_fds)[2];
	int				*pids;
}					t_pipex;
typedef struct s_minishell
{
	char			**env;
	t_pipex			pipex;
}					t_minishell;

#endif
