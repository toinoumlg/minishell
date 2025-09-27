#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <termios.h>

volatile sig_atomic_t g_heredoc_interrupted = 0;

void sigint_handler_main(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 2;  // ← AJOUTEZ cette ligne !
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    close(STDIN_FILENO);
    rl_done = 1;
}

void set_signals(void)
{
    signal(SIGINT, sigint_handler_main);
    signal(SIGQUIT, SIG_IGN);
}

void set_signals_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);  // Comportement par défaut normal
}


void set_signals_heredoc(void)
{
    signal(SIGINT, heredoc_sigint_handler);
    signal(SIGQUIT, SIG_IGN);  // Ignore dans heredoc aussi
}

int is_heredoc_interrupted(void)
{
    return (g_heredoc_interrupted == 1);
}

void reset_heredoc_state(void)
{
    g_heredoc_interrupted = 0;
}

void disable_ctrl_backslash(void)
{
    struct termios term;
    
    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return;
    term.c_cc[VQUIT] = _POSIX_VDISABLE;  // Désactive Ctrl+\ au niveau terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enable_ctrl_backslash(void)
{
    struct termios term;
    
    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return;
    term.c_cc[VQUIT] = 28;  // Restaure Ctrl+\ (ASCII 28)
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}