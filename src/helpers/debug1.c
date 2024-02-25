/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:24:13 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:51:09 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redirs(t_redir *head)
{
	while (head)
	{
		printf("REDIRECTION: ");
		if (head->operator == GREAT)
			printf(">");
		else if (head->operator == LESS)
			printf("<");
		else if (head->operator == DGREAT)
			printf(">>");
		else if (head->operator == DLESS)
			printf("<<");
		printf(" | WORD: %s\n", head->word);
		head = head->next;
	}
}

static void	print_words(t_word *head)
{
	while (head)
	{
		printf("WORD: %s \n", head->word);
		printf("----------------------\n");
		head = head->next;
	}
}

void	print_baobab(t_minivault *minivault)
{
	int	i;

	i = 0;
	if (!minivault->baobab || !minivault->baobab->pipeline)
		return ;
	while (minivault->baobab->pipeline[i])
	{
		if (i != 0)
			printf("\n----------------------\n");
		printf("Command: %d\n", i);
		printf("\n----------------------\n");
		if (minivault->baobab->pipeline[i]->redir_in)
			print_redirs(minivault->baobab->pipeline[i]->redir_in);
		if (minivault->baobab->pipeline[i]->words)
			print_words(minivault->baobab->pipeline[i]->words);
		if (minivault->baobab->pipeline[i]->redir_out)
			print_redirs(minivault->baobab->pipeline[i]->redir_out);
		i++;
	}
}
