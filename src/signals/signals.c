
#include "minishell.h"

void	sig_int_handler(int signo) // ctrl + 'C'
{

	if (signo == SIGINT)
	{
		if (readlinedata()->line == NULL) // Handle EOF
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			(void) signo;
		}
	}
}

void	sig_term_handler(int signo) // ctrl + 'D'
{
	if (signo == SIGTERM)
	{	
		return ;
	}
}


void	set_signals(void)
{
	if (signal(SIGINT, sig_int_handler) == SIG_ERR)
		perror("Siganl: SIGINT");
	if (signal(SIGTERM, sig_term_handler) == SIG_ERR)
		perror("Siganl: SIGTERM");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Siganl: SIGQUIT");
}
