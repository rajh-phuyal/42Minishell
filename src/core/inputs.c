/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:51 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 17:07:01 by jalves-c         ###   ########.fr       */
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

void	handle_input(t_minivault *minivault, char *input)
{
	set_signals(SIG_STATE_MAIN);
	if (!input)
		_exit_vault(minivault, NULL, STDOUT_FILENO);
	if (g_signal_status == 130)
		set_env(minivault, "?", ft_itoa(130), (1 << 1));
	else if (input && input[FIRST_ELEM] == '\0')
	{
		minivault->cycles++;
		free(input);
		return ;
	}
	minivault->line = input;
	if (lexer(minivault, input))
	{
		grow_baobab(minivault);
		executor(minivault, minivault->baobab->pipeline);
		set_signals(SIG_STATE_MAIN);
	}
	minivault->cycles++;
	cycle_reset(minivault);
}
