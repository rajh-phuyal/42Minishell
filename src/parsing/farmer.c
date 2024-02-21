/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farmer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:06 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 22:13:15 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_content_type token_type, t_token *tokens)
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

// void	open_pipes(t_minivault *minivault, int i, int command_count)
// {
// 	while (i < FOPEN_MAX)
// 		ft_bzero(minivault->baobab->pipe_fd[i++], 2);
// 	i = 0;
// 	while (i < command_count - 1 && i < FOPEN_MAX)
// 		pipe(minivault->baobab->pipe_fd[i++]);
// }

/*
To calculate the position of the cmd
asume there is always a command if it reaches this point
start with 1, everything after the first index is asumed as middle (1 + (i > 0))
to find the last we can add one more to the first output
making it 3 (1 + (i > 0) + (i == (command_count - 1))).
Lastly subtract 2 if there is only one command to make the
final output:
(1 + (i > 0) + (i == (command_count - 1))) - (2 * (command_count == 1));
*/
void	grow_baobab(t_minivault	*minivault)
{
	int	i;
	int	command_count;

	command_count = 1 + count_tokens(PIPE, minivault->tokens);
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
		// minivault->baobab->pipeline[i]->pos = (1 + (i > 0)
		// 		+ (i == (command_count - 1)))
		// 	- (2 * (command_count == 1));
		i++;
	}
}
