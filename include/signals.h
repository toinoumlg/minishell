/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 01:00:00 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/18 01:00:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <sys/types.h> /* pid_t */

/* -------------------------------------------------------------------------- */
/* Gestion du terminal (TTY)                                                  */
/* -------------------------------------------------------------------------- */

/* Sauvegarde l'état initial du TTY (à appeler une seule fois au démarrage) */
void	tty_save_initial_state(void);

/* Restaure l'état initial du TTY (avant chaque readline, après enfants) */
void	tty_restore_initial_state(void);

/* -------------------------------------------------------------------------- */
/* Handlers signaux du shell (prompt)                                         */
/* -------------------------------------------------------------------------- */

/* Pose les handlers du prompt :
   - SIGINT : imprime une NL + reset la ligne (ne quitte pas)
   - SIGQUIT : ignoré */
void	set_signals(void);

/* -------------------------------------------------------------------------- */
/* Handlers signaux enfants                                                    */
/* -------------------------------------------------------------------------- */

/* Pour les enfants exécutés par execve :
   - SIGINT / SIGQUIT : comportement par défaut (SIG_DFL) */
void	set_signals_child(void);

/* Pour un enfant heredoc :
   - SIGINT : tue l’enfant (exit 130)
   - SIGQUIT : ignoré */
void	set_signals_heredoc(void);

/* -------------------------------------------------------------------------- */
/* Utilitaires heredoc                                                         */
/* -------------------------------------------------------------------------- */

/* A appeler dans le parent après un waitpid heredoc pour restaurer proprement
   les handlers prompt et mémoriser si SIGINT est arrivé. */
void	restore_after_heredoc(int status);

/* Renvoie vrai si le dernier heredoc a été interrompu par SIGINT. */
int		heredoc_was_interrupted(void);

/* -------------------------------------------------------------------------- */
/* Wrapper readline personnalisé                                              */
/* -------------------------------------------------------------------------- */

/* Appel à readline qui restaure le TTY et réinstalle les handlers avant prompt */
char	*ms_readline(const char *prompt);

#endif
