#include "minishell.h"

/* explain this */
void	sig_int_handler(int signo) // ctrl + 'C'
{
	if (signo == SIGINT)
	{
		write(1,"\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void)signo;
	}
}
// TODO: ctrl + C to terminate the process

/* This works for now but has to be changed*/
void	sig_term_handler(int signo) // ctrl + 'D'
{
	(void)signo;
	write(1, "hello\n\n", 7);
	// if (signo == SIGTERM)
	// { 
	// 	free(readlinedata()->line);
	// 	exit (1);
	// }
}


void	set_signals(void)
{
	// if (signal(SIGQUIT, sig_term_handler) == SIG_ERR)
	// 	perror("Siganl: SIGTERM");
	if (signal(SIGINT, sig_int_handler) == SIG_ERR)
		perror("Siganl: SIGINT");
	// if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	// 	perror("Siganl: SIGQUIT");
}
