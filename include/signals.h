/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:10:00 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 17:05:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/*
** Tout l'état vit dans minishell->sigctx (défini dans minishell.h).
** On lie le contexte courant avec signals_bind_minishell(&minishell).
*/

void	signals_bind_minishell(t_minishell *ms);

void	tty_save_initial_state(void);
void	tty_restore_initial_state(void);

void	set_signals(void);         /* handlers du prompt (parent prêt à lire) */
void	set_signals_child(void);   /* enfant normal (avant execve) */
void	set_signals_heredoc(void); /* enfant heredoc */

void	restore_after_heredoc(int status); /* parent, après waitpid du heredoc */
int		heredoc_was_interrupted(void);

#endif
