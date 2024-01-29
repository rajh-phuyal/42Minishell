/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:17:38 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:17:40 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	liberate_vector(char **vector)
{
	int	i;

	i = 0;
	if (!vector)
		return ;
	while (vector && vector[i])
		free(vector[i++]);
	free(vector);
}

void	liberate_tokens(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		// free(head->content);
		free(head);
		head = tmp;
	}
}

void	liberate_envs(t_envs *head)
{
	t_envs	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

// liberates the memory allocated for the tokens and the baobab tree
void	liberation(t_minivault *minivault)
{
	cycle_reset(minivault);
	close_readline();
	if (minivault->path)
		liberate_vector(minivault->path);
	if (minivault->envs)
		liberate_envs(minivault->envs);
}
