#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void    set_signals(void);
void    set_signals_child(void);
void    set_signals_heredoc(void);

#endif