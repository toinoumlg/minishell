/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 01:10:00 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/18 01:10:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* -------------------------------------------------------------------------- */
/* État TTY initial sauvegardé au démarrage                                   */
/* -------------------------------------------------------------------------- */

static struct termios	g_tty_saved;
static int				g_tty_saved_ok = 0;

/* Flag: dernier heredoc interrompu par SIGINT ? */
static volatile sig_atomic_t	g_hd_interrupted = 0;

/* -------------------------------------------------------------------------- */
/* Helpers locaux                                                              */
/* -------------------------------------------------------------------------- */

static void	set_sa(struct sigaction *sa, void (*handler)(int), int flags)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = flags;
	sa->sa_handler = handler;
}

/* Handler SIGINT au prompt: imprime une NL et redessine un prompt propre */
static void	sigint_handler_prompt(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* Handler SIGINT dans l'enfant heredoc: sortir tout de suite avec 130 */
static void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	/* Indiquer au parent que c'était une interruption */
	/* (Le parent peut aussi déduire via waitpid + WTERMSIG == SIGINT) */
	_exit(130);
}

/* -------------------------------------------------------------------------- */
/* API publique                                                                */
/* -------------------------------------------------------------------------- */

void	tty_save_initial_state(void)
{
	struct termios t;

	if (tcgetattr(STDIN_FILENO, &t) == 0)
	{
		g_tty_saved = t;
		g_tty_saved_ok = 1;
	}
}

void	tty_restore_initial_state(void)
{
	if (g_tty_saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &g_tty_saved);
}

void	set_signals(void)
{
	struct sigaction	sa;

	/* Prompt: Ctrl-C -> NL + ligne vide, Ctrl-\ ignoré */
	set_sa(&sa, sigint_handler_prompt, 0);
	sigaction(SIGINT, &sa, NULL);

	set_sa(&sa, SIG_IGN, 0);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signals_child(void)
{
	struct sigaction	sa;

	/* Enfant classique: comportements par défaut */
	set_sa(&sa, SIG_DFL, 0);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	/* Enfant heredoc: Ctrl-C -> stop immédiat avec 130 */
	set_sa(&sa, sigint_handler_heredoc, 0);
	sigaction(SIGINT, &sa, NULL);

	/* Ctrl-\ ignoré pendant la saisie heredoc */
	set_sa(&sa, SIG_IGN, 0);
	sigaction(SIGQUIT, &sa, NULL);
}

void	restore_after_heredoc(int status)
{
	/* Remet un TTY sain (au cas où) */
	tty_restore_initial_state();

	/* Marque l'interruption si besoin */
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		g_hd_interrupted = 1;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		g_hd_interrupted = 1;
	else
		g_hd_interrupted = 0;

	/* Nettoie l'état de readline pour éviter un prompt sale */
	rl_replace_line("", 0);
	rl_on_new_line();

	/* Réinstalle les handlers du prompt */
	set_signals();
}

int	heredoc_was_interrupted(void)
{
	int	was;

	was = (int)g_hd_interrupted;
	g_hd_interrupted = 0;
	return (was);
}
