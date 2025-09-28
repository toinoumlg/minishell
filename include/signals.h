/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:15:42 by yalaatik          #+#    #+#             */
/*   Updated: 2025/09/28 13:47:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// signals.h
#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

// Déclaration de la variable globale (avec extern)
extern sig_atomic_t	g_sig;

// Vos fonctions
void				sigint_handler_main(int sig);
void				heredoc_sigint_handler(int sig);
void				set_signals(void);
void				set_signals_child(void);
void				set_signals_heredoc(void);

#endif
