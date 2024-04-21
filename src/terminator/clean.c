/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:13 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/21 19:03:46 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	liberate_words(t_word *head)
{
	t_word	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	liberate_command(t_command *command)
{
	if (!command)
		return ;
	liberate_words(command->words);
	liberate_redir(command->redir_in);
	liberate_redir(command->redir_out);
	if (command->exec_path)
		free(command->exec_path);
	if (command->infile_fd != STDIN && command->infile_fd != -1)
		close(command->infile_fd);
	if (command->outfile_fd != STDOUT && command->outfile_fd != -1)
		close(command->outfile_fd);
	if (command->fd[0] > 1)
		close(command->fd[0]);
	if (command->fd[1] > 1)
		close(command->fd[1]);
	free(command);
}
