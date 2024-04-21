/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:06:11 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:19:36 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	liberate_words(t_word *head)
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
	if (command->fd[WRITE] != STDIN)
		close(command->fd[WRITE]);
	if (command->fd[READ] != STDOUT)
		close(command->fd[READ]);
	free(command);
}
