/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farmer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:04:52 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:04:53 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(t_content_type token_type, t_token *tokens)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current)
	{
		if (current->type == token_type)
			i++;
		current = current->next;
	}
	return (i);
}

void	grow_baobab(t_minivault	*minivault)
{
	int	i;
	int	command_count;

	command_count = 1 + count_tokens(PIPE, minivault->tokens);
	minivault->cmd_count = command_count;
	minivault->baobab = ft_calloc(1, sizeof(t_baobab));
	minivault->baobab->pipeline = ft_calloc(sizeof(t_command *), \
									(command_count + 2));
	i = 0;
	minivault->baobab->pipeline[command_count] = NULL;
	while (i < command_count)
	{
		minivault->baobab->pipeline[i] = NULL;
		minivault->baobab->pipeline[i] = split_list(minivault, \
				minivault->tokens, PIPE);
		if (minivault->baobab->pipeline[i] == NULL)
			break ;
		i++;
	}
}
