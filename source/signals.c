#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

// Handler pour SIGINT (Ctrl+C) dans le processus principal
void sigint_handler_main(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

// Handler pour SIGQUIT (Ctrl+\) dans le processus principal - ignore
void sigquit_handler_main(int sig)
{
    (void)sig;
    // Ne rien faire - ignorer le signal
}

// Configuration des signaux pour le processus principal
void set_signals(void)
{
    struct sigaction sa_int, sa_quit;
    
    // Configuration pour SIGINT (Ctrl+C)
    sa_int.sa_handler = sigint_handler_main;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);
    
    // Configuration pour SIGQUIT (Ctrl+\) - ignorer
    sa_quit.sa_handler = sigquit_handler_main;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

// Configuration des signaux pour les processus enfants normaux
void set_signals_child(void)
{
    struct sigaction sa_int, sa_quit;
    
    // Remettre le comportement par défaut pour les enfants
    sa_int.sa_handler = SIG_DFL;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    
    sa_quit.sa_handler = SIG_DFL;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

// Configuration des signaux pour heredoc
void set_signals_heredoc(void)
{
    struct sigaction sa_int, sa_quit;
    
    // Comportement par défaut pour heredoc
    sa_int.sa_handler = SIG_DFL;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    
    sa_quit.sa_handler = SIG_DFL;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}