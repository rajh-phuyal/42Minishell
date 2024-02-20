#include "minishell.h"

void	sig_handler_main(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_status = 1; // ! when is this being checked?
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_parent(int signo)
{
	if (signo == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signo == SIGINT)
		write(STDERR_FILENO, "\n", 1);
}

void	sig_handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_status = 2; // ! when is this being checked?
		write(STDOUT, "\n", 1);
		close(STDIN_FILENO);
	}
}

static void	set_additional_signals(t_sig_state	sig_state)
{
	if (sig_state == SIG_STATE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig_state == SIG_STATE_BUILTIN)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_HD_CHILD)
	{
		signal(SIGINT, sig_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	set_signals(t_sig_state	sig_state)
{
	if (sig_state == SIG_STATE_MAIN)
	{
		signal(SIGINT, sig_handler_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_PARENT)
	{
		signal(SIGINT, sig_handler_parent);
		signal(SIGQUIT, sig_handler_parent);
	}
	else if (sig_state == SIG_STATE_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		set_additional_signals(sig_state);
}
