/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:51 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:29:52 by jalves-c         ###   ########.fr       */
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
