/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:30:00 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 01:02:38 by jalves-c         ###   ########.fr       */
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

void	liberate_redir(t_redir *head)
{
	t_redir	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->fd != -1)
			close(tmp->fd);
		free(tmp);
	}
}

void	reset_path(t_minivault *minivault)
{
	int	i;

	i = 0;
	while (minivault->path && minivault->path[i])
	{
		free(minivault->path[i]);
		minivault->path[i++] = NULL;
	}
	if (minivault->path)
		free(minivault->path);
	if (get_env(minivault, "PATH"))
		minivault->path = ft_split(get_env(minivault, "PATH"), ':');
	else
		minivault->path = NULL;
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
	free(command);
}

void	liberate_baobab(t_minivault *minivault, t_baobab *head)
{
	int	i;

	(void)minivault; //!tira-me esta merda
	i = 0;
	if (!head)
		return ;
	while (head->pipeline && head->pipeline[i])
		liberate_command(head->pipeline[i++]);
	free(head->pipeline);
	free(head);
	head = NULL;
}

void	cycle_reset(t_minivault *minivault)
{
	if (minivault->baobab)
		liberate_baobab(minivault, minivault->baobab);
	if (minivault->tokens)
		liberate_tokens(minivault->tokens);
	else if (minivault->input)
		liberate_vector(minivault->input);
	empty_fd_catcher(minivault);
	reset_path(minivault);
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
}

void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
}