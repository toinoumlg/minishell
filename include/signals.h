// signals.h
#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>

// Déclaration de la variable globale (avec extern)
extern volatile sig_atomic_t g_heredoc_interrupted;

// Vos fonctions
void sigint_handler_main(int sig);
void sigquit_handler_main(int sig);
void heredoc_sigint_handler(int sig);
void set_signals(void);
void set_signals_child(void);
void set_signals_heredoc(void);
int is_heredoc_interrupted(void);
void reset_heredoc_state(void);
void enable_ctrl_backslash(void);
void disable_ctrl_backslash(void);
void reset_heredoc_display_flag(void);

#endif