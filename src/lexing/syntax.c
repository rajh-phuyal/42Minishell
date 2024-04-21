/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:25:04 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/21 11:46:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_syntax_empty_after_token(t_minivault *minivault, \
			t_token	*current)
{
	if (current && current->type == REDIRECTION && current->next == NULL)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token ", "`newline'", NULL);
		return (false);
	}
	if (current && current->type == PIPE && current->next == NULL)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token ", "`|'", NULL);
		return (false);
	}
	return (true);
}

static bool	check_syntax_token_after_token(t_minivault *minivault, \
			t_token	*current)
{
	if (current && current->next && \
		current->type == REDIRECTION && current->next->type == REDIRECTION)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token ", "`>'", NULL);
		return (false);
	}
	if (current && current->next && \
		current->type == PIPE && current->next->type == PIPE)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token ", "`|'", NULL);
		return (false);
	}
	return (true);
}

static bool	pipe_at_beginning(t_minivault *minivault, \
			t_token	*current)
{
	if (current && current->type == PIPE)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token ", "`|'", NULL);
		return (true);
	}
	return (false);
}

bool	check_syntax(t_minivault *minivault)
{
	t_token	*current;

	if (!minivault->tokens)
		return (false);
	current = minivault->tokens;
	if (pipe_at_beginning(minivault, current))
		return (false);
	while (current)
	{
		if (!check_syntax_empty_after_token(minivault, current))
			return (false);
		if (!check_syntax_token_after_token(minivault, current))
			return (false);
		if (current && current->next && \
			current->type == REDIRECTION && current->next->type == PIPE)
		{
			error(minivault, FAILURE, true, \
			"syntax error near unexpected token ", "`|'", NULL);
			return (false);
		}
		current = current->next;
	}
	return (true);
}
