/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:54:40 by yalaatik          #+#    #+#             */
/*   Updated: 2025/09/27 18:54:43 by yalaatik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <termios.h>

volatile sig_atomic_t	g_heredoc_interrupted = 0;

void	sigint_handler_main(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 2;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler_main);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	disable_ctrl_backslash(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_ctrl_backslash(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_cc[VQUIT] = 28;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
