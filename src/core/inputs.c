/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/26 17:12:12 by rajphuyal        ###   ########.fr       */
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

void	handle_input(t_minivault *minivault, char *input)
{
	if (lexer(minivault, input))
		grow_baobab(minivault);
	executor(minivault, minivault->baobab->pipeline);
	cycle_reset(minivault);
}
