/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:44 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 18:19:22 by amalangu         ###   ########.fr       */
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
	int				pos;
	char			*string;
	int				is_word;
	int				is_pipe;
	int				is_redirect_input;
	int				is_redirect_output;
	int				is_here_doc;
	int				is_append_file;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	t_cmd			*cmds;
	int				parse_error;
	int				exit;
}					t_minishell;

#endif
