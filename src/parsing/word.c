/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:06:04 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:06:05 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word	*create_word_node(t_token *token)
{
	t_word	*word;

	if (!token || !(token->type == LITERAL || token->type == QUOTED))
		return (NULL);
	word = ft_calloc(1, sizeof(t_word));
	if (!word)
		return (NULL);
	word->word = token->content;
	word->next = NULL;
	return (word);
}

void	add_word(t_word **word_list, t_token *token)
{
	t_word	*word;
	t_word	*head;

	word = NULL;
	if (token)
		word = create_word_node(token);
	if (!word)
		return ;
	head = (*word_list);
	if (!head)
	{
		*word_list = word;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = word;
}
