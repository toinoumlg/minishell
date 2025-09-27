/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:39 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/26 14:34:22 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "exec.h"
#include "parser/parse_read_line.h"
#include "signals.h"
#include <readline/readline.h>
#include <sys/wait.h>

void	wait_for_childrens(t_minishell *minishell)
{
	int	i;
	int	status;
	int	sig;

	i = 0;
	if (!minishell->i)
		return ;
	
	// Ignorer les signaux pendant l'attente (comme votre collègue)
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	
	while (i < minishell->size)
		waitpid(minishell->pids[i++], &status, 0);
	
	// Restaurer les signaux normaux
	set_signals();
	
	// Gestion des signaux (comme votre collègue)
	if (WIFEXITED(status))
		minishell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) {
		sig = WTERMSIG(status);
		minishell->last_status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);  // ← LA solution !
	}
	
	if (minishell->pids)
		free(minishell->pids);
	minishell->pids = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_minishell minishell;

    if (!isatty(0) || !isatty(1) || !isatty(2))
        return (1);
    set_envp(&minishell, envp);
    disable_ctrl_backslash();
    set_signals();
    
    while (argv && argc) {
        g_heredoc_interrupted = 0;  // ← Reset comme votre collègue
        minishell.read_line = readline("minishell> ");
        
        if (!minishell.read_line) {
            write(1, "exit\n", 5);
            break;
        }
        
        parse_read_line(&minishell);
        exec(&minishell);
        wait_for_childrens(&minishell);
    }
    enable_ctrl_backslash();
    return (0);
}