/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:16 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 22:08:26 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_first(t_minivault *minivault)
{
	close(minivault->baobab->pipe_fd[FIRST_ELEM][WRITE]);
}

void	close_pipes_middle(t_minivault *minivault, int pos)
{
	close(minivault->baobab->pipe_fd[pos - 1][WRITE]);
	close(minivault->baobab->pipe_fd[pos - 1][READ]);
	close(minivault->baobab->pipe_fd[pos][WRITE]);
}

void	close_pipes_last(t_minivault *minivault)
{
	int	last_pipe_index;

	last_pipe_index = count_tokens(PIPE, minivault->tokens) - 1;
	close(minivault->baobab->pipe_fd[last_pipe_index][READ]);
}

void	close_pipes(int in, int out)
{
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
}
