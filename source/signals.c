/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:10:00 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 19:25:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/* Pointeur global interne vers le minishell courant (utilisé par les handlers) */
static t_minishell	*g_ms = NULL;

/* -------------------------------------------------------------------------- */
/* Binding                                                                    */
/* -------------------------------------------------------------------------- */
void	signals_bind_minishell(t_minishell *ms)
{
	g_ms = ms;
}

/* -------------------------------------------------------------------------- */
/* Helpers TTY                                                                */
/* -------------------------------------------------------------------------- */
static void	tty_force_sane(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == 0)
	{
		/* réactive echo, mode canonique et signaux */
		t.c_lflag |= ECHO;
		t.c_lflag |= ICANON;
		t.c_lflag |= ISIG;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
}

void	tty_save_initial_state(void)
{
	if (g_ms == NULL)
		return ;
	if (tcgetattr(STDIN_FILENO, &g_ms->sigctx.tty_saved) == 0)
		g_ms->sigctx.tty_saved_ok = 1;
}

void	tty_restore_initial_state(void)
{
	if (g_ms == NULL)
		return ;
	if (g_ms->sigctx.tty_saved_ok != 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &g_ms->sigctx.tty_saved);
		/* au cas où l’état sauvegardé aurait été appliqué en plein milieu
		   d’un cycle readline interrompu : garantis un TTY “sain” */
		tty_force_sane();
	}
}

/* -------------------------------------------------------------------------- */
/* Handlers                                                                    */
/* -------------------------------------------------------------------------- */
static void	sigint_handler_prompt(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

static void	sigquit_handler_ignored(int signo)
{
	(void)signo;
}

/* enfant heredoc: renvoie 130 */
static void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	_exit(130);
}

/* -------------------------------------------------------------------------- */
/* set_signals : handlers du prompt (parent prêt à lire)                      */
/* -------------------------------------------------------------------------- */
void	set_signals(void)
{
	struct sigaction	sa;

	if (g_ms != NULL)
		g_ms->sigctx.hd_interrupted = 0;
	rl_catch_signals = 0;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sa.sa_handler = sigint_handler_prompt;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = sigquit_handler_ignored;
	sigaction(SIGQUIT, &sa, NULL);

	/* assure un TTY propre au moment d’afficher le prompt */
	tty_force_sane();
}

/* -------------------------------------------------------------------------- */
/* Enfant normal (avant execve)                                               */
/* -------------------------------------------------------------------------- */
void	set_signals_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/* -------------------------------------------------------------------------- */
/* Enfant heredoc                                                             */
/* -------------------------------------------------------------------------- */
void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sa.sa_handler = sigint_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/* -------------------------------------------------------------------------- */
/* Post-heredoc (parent)                                                      */
/* -------------------------------------------------------------------------- */
void	restore_after_heredoc(int status)
{
	if (g_ms != NULL)
		g_ms->sigctx.hd_interrupted = 0;
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == SIGINT)
		{
			if (g_ms != NULL)
				g_ms->sigctx.hd_interrupted = 1;
			/* clean affichage readline côté parent */
			rl_replace_line("", 0);
			rl_on_new_line();
			write(STDOUT_FILENO, "\n", 1);
			rl_redisplay();
		}
	}
	/* restaure l’état enregistré ET s’assure de l’echo/canonique */
	tty_restore_initial_state();
	tty_force_sane();
}

int	heredoc_was_interrupted(void)
{
	if (g_ms == NULL)
		return (0);
	if (g_ms->sigctx.hd_interrupted != 0)
		return (1);
	return (0);
}
