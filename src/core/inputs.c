/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/16 21:13:58 by rajphuyal        ###   ########.fr       */
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

	line = readline("minibaiters $ ");
	if (line && *line)
		add_history(line);
	return (line);
}

void	handle_input(t_minivault *minivault, char *input, char **envs)
{
	init_minivault(minivault, envs);
	lexer(minivault, input);
	grow_baobab(minivault);
	// call_debug(minivault);
	liberation(minivault);
}
