/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:09:41 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:09:42 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	reset_path(t_minivault *minivault)
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

void	liberate_baobab( t_baobab *head)
{
	int	i;

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
		liberate_baobab(minivault->baobab);
	if (minivault->tokens)
		liberate_tokens(minivault->tokens);
	else if (minivault->input)
		liberate_vector(minivault->input);
	reset_path(minivault);
	release_fds(minivault);
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
}
