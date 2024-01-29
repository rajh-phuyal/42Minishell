
#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef enum	e_sig_state
{
	SIG_STATE_MAIN,
	SIG_STATE_PARENT,
	SIG_STATE_CHILD,
	SIG_STATE_CHILD_BUILTIN,
	SIG_STATE_HD_CHILD,
	SIG_STATE_IGNORE
}				t_sig_state;

# define SIGNAL_EXIT_HD 2

void	set_signals(t_sig_state	sig_state);

#endif