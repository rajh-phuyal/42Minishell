/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/28 00:03:09 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_readline(void)
{
	rl_initialize();
	rl_bind_key('\t', rl_complete);
}

void	close_readline(void)
{
	clear_history();
}

char	*readaline(void)
{
	char	*line;

	line = readline("minishell (⌘ ↩︎) $ ");
	if (line && *line)
		add_history(line);
	return (line);
}

void	handle_input(char *input)
{
	lexer(input);
}
