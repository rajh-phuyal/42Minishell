/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:51 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/14 01:01:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// closes the readline library
void	close_readline(void)
{
	clear_history();
}

char	*readaline(void)
{
	char	*line;

	line = readline("minibaiters$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

void	handle_interrupt(t_minivault *minivault)
{
	if (g_signal_status != SIGINTERRUPT)
		return ;
	set_env(minivault, "?", ft_itoa(SIGINTERRUPT), (1 << 1));
	minivault->cycles++;
}

void	handle_input(t_minivault *minivault, char *input)
{
	set_signals(SIG_STATE_MAIN);
	if (!input)
		_exit_vault(minivault, NULL, STDOUT_FILENO);
	handle_interrupt(minivault);
	if (input && input[FIRST_ELEM] == '\0')
	{
		minivault->cycles++;
		free(input);
		return ;
	}
	minivault->line = input;
	if (lexer(minivault, input))
	{
		minivault->is_exec = 1;
		grow_baobab(minivault);
		executor(minivault, minivault->baobab->pipeline);
		set_signals(SIG_STATE_MAIN);
	}
	minivault->cycles++;
	cycle_reset(minivault);
	set_signals(SIG_STATE_MAIN);
}
