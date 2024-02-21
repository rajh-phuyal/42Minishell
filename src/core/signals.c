/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:58 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 18:48:27 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler_main(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_status = 130;
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_handler_parent(int signo)
{
	if (signo == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signo == SIGINT)
		write(STDERR_FILENO, "\n", 1);
}

static void	sig_handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_status = SIGNAL_EXIT_HD;
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
