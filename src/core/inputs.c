/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/06 18:00:01 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// closes the readline library
void	close_readline(void)
{
	clear_history();
}

// just reads a line form the terminal
char	*readaline(void)
{
	char	*line;

	line = readline("minibaiters $ ");
	if (line && *line)
		add_history(line); // doing it for later user
	return (line);
}

void	handle_input(t_minivault *minivault, char *input)
{
	lexer(minivault, input);
}
