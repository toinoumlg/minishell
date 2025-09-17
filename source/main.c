/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/18 02:05:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env/init_envp.h"
#include "parser/parse_read_line.h"
#include "signals.h"
#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */
/* Helpers signaux pour la phase d'exécution                                  */
/* -------------------------------------------------------------------------- */
static void	parent_ignore_signals_during_exec(void)
{
	struct sigaction sa;

	/* Pendant l'exec/wait: le parent ignore SIGINT/SIGQUIT
	   -> le signal ne déclenche PAS notre handler prompt
	   -> pas de double "minishell>" après Ctrl-C sur un binaire type cat */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	parent_restore_prompt_signals(void)
{
	/* On remet nos handlers du prompt (SIGINT propre, SIGQUIT ignoré) */
	set_signals();
}

/* -------------------------------------------------------------------------- */
/* Affichage cohérent en fonction du status d'un enfant                        */
/* -------------------------------------------------------------------------- */
static int	update_status_and_display(int status)
{
	int	code;
	int	sig;

	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		return (code);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		/* Ici, on affiche nous-mêmes, une seule fois, après waitpid */
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		code = 128 + sig;
		return (code);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Attente des enfants lancés par exec()                                      */
/* - Met à jour minishell->last_status avec le *dernier* enfant attendu       */
/* - Affiche correctement après signaux (évite prompts doublés / "^\")        */
/* -------------------------------------------------------------------------- */
static void	wait_for_childrens(t_minishell *minishell)
{
	int		i;
	int		status;
	int		last_status_code;
	int		waited_any;

	if (!minishell->pids || minishell->size <= 0)
		return ;

	i = 0;
	last_status_code = minishell->last_status;
	waited_any = 0;
	while (i < minishell->size)
	{
		pid_t pid;

		pid = minishell->pids[i];
		if (pid > 0)
		{
			if (waitpid(pid, &status, 0) == pid)
			{
				last_status_code = update_status_and_display(status);
				waited_any = 1;
			}
		}
		i++;
	}
	if (waited_any)
		minishell->last_status = last_status_code;
	free(minishell->pids);
	minishell->pids = NULL;
}

/* -------------------------------------------------------------------------- */
/* Readline wrapper: garantit nos handlers au prompt                          */
/* -------------------------------------------------------------------------- */
char	*ms_readline(const char *prompt)
{
	/* Restaure TTY si besoin et remet les handlers du prompt */
	tty_restore_initial_state();
	set_signals();
	return (readline(prompt));
}

/* -------------------------------------------------------------------------- */
/* main                                                                       */
/* -------------------------------------------------------------------------- */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;

	/* Readline: on gère nous-mêmes SIGINT/SIGQUIT au prompt */
	extern int rl_catch_signals;
	rl_catch_signals = 0;

	/* Mémorise l'état TTY initial et pose les handlers du prompt */
	tty_save_initial_state();
	set_signals();

	/* Environnement */
	init_envp(&minishell, envp);

	/* Boucle principale */
	while (1)
	{
		minishell.read_line = ms_readline("minishell> ");
		parse_read_line(&minishell);

		/* IMPORTANT: le parent ignore les signaux pendant l'exécution */
		parent_ignore_signals_during_exec();

		exec(&minishell);
		wait_for_childrens(&minishell);

		/* Puis on restaure les handlers du prompt */
		parent_restore_prompt_signals();
	}
	return (0);
}
