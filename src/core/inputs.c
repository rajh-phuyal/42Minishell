/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:19:59 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:20:01 by jalves-c         ###   ########.fr       */
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
	else if (input && input[FIRST_ELEM] == '\0')
	{
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
	cycle_reset(minivault);
	minivault->cycles++;
}
