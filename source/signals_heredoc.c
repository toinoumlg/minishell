/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaatik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:18:35 by yalaatik          #+#    #+#             */
/*   Updated: 2025/09/27 20:18:39 by yalaatik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <termios.h>

void	set_signals_heredoc(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	is_heredoc_interrupted(void)
{
	return (g_heredoc_interrupted == 1);
}

void	reset_heredoc_state(void)
{
	g_heredoc_interrupted = 0;
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	close(STDIN_FILENO);
	rl_done = 1;
}
