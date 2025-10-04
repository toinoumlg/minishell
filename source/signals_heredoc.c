/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:18:35 by yalaatik          #+#    #+#             */
/*   Updated: 2025/10/04 13:42:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <unistd.h>

void	heredoc_sigint_handler(int sig)
{
	write(1, "^C\n", 3);
	close(STDIN_FILENO);
	g_sig = sig;
}

void	set_signals_heredoc(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
