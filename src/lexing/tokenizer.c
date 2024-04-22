/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:03:59 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:04:00 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token_type(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, "<", 2) || \
			!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (REDIRECTION);
	else if (token_is_quoted(token) == true)
		return (QUOTED);
	return (LITERAL);
}

static t_token	*create_new(char *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->type = get_token_type(token);
	new->content = remove_quotes(token, 0);
	free(token);
	return (new);
}

static void	add_token(t_minivault *minivault, char *token)
{
	t_token	*head;
	t_token	*token_node;

	head = minivault->tokens;
	token_node = create_new(token);
	if (!head)
	{
		minivault->tokens = token_node;
		return ;
	}
	if (head && !head->next)
	{
		head->next = token_node;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = token_node;
}

void	tokenizer(t_minivault *minivault)
{
	int	i;

	i = 0;
	while (minivault->input && minivault->input[i])
	{
		if (minivault->input[i] && \
			!(minivault->input[i][FIRST_ELEM] == PLACEHOLDER[FIRST_ELEM]))
			add_token(minivault, minivault->input[i]);
		else
			free(minivault->input[i]);
		i++;
	}
	free(minivault->input);
	minivault->input = NULL;
}
