/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:25 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:18:28 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* syntax errors
 ! ERROR 1
 ? Command: |
 ! ERROR: bash: syntax error near unexpected token `|'
 -------------------------------------------------------------------------------
 ! ERROR 2
 ? Command: | |
 ! ERROR: bash: syntax error near unexpected token `|'
 -------------------------------------------------------------------------------
 ? Command: <
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------------
 ? Command: >
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------------
 ! ERROR 3
 ? Command: >>
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------------
 ? Command: <<
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------------
 * If the file "file" exists, nothing happens, and the prompt returns.
 * If the file "file" does not exist, an error is printed.
 ! ERROR: bash: file: No such file or directory
 -------------------------------------------------------------------------------
 ? Command: > file
 * If the file "file" does not exist, it will be created.
 * If the file "file" already exists, 
 * its contents will be replaced with nothing (i.e., the file will be emptied).
 -------------------------------------------------------------------------------
 ? Command: >> file
 * If the file "file" does not exist, it will be created.
 * If the file "file" already exists, the existing content won't be modified.
 -------------------------------------------------------------------------------
*/

bool	check_syntax(t_minivault *minivault)
{
	t_token	*current;

	if (!minivault->tokens)
		return (false);
	current = minivault->tokens;
	if (current->type == PIPE && current->next == NULL)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token", "`|'", NULL);
		return (false);
	}
	while (current)
	{
		if (current && current->type == REDIRECTION && current->next == NULL)
		{
			error(minivault, FAILURE, true, \
			"syntax error near unexpected token", "`newline'", NULL);
			return (false);
		}
		if (current && current->next && \
		current->type == REDIRECTION && current->next->type == REDIRECTION)
		{
			error(minivault, FAILURE, true, \
			"syntax error near unexpected token", "`>'", NULL);
			return (false);
		}
		if (current && current->type == PIPE && current->next == NULL)
		{
			// command: cmd |
			// dont know if the prompt should return or should just print error
			error(minivault, FAILURE, true, \
			"syntax error near unexpected token", "`|'", NULL);
			return (false);
		}
		if (current && current->next && \
		current->type == PIPE && current->next->type == PIPE)
		{
			error(minivault, FAILURE, true, \
			"syntax error near unexpected token", "`|'", NULL);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	is_valid(t_minivault *minivault, const char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str > LOWER_BOUND && *str < UPPER_BOUND)
		{
			str++;
			continue ;
		}
		else
		{
			error(minivault, FAILURE, true, "syntax error ", NULL);
			return (false);
		}
		str++;
	}
	return (true);
}

/* atempting to create tokens based on the 
 * received input str for the readline 
*/
bool	lexer(t_minivault *minivault, char *input)
{
	if (!input || !is_valid(minivault, input))
		return (false);
	strextract(minivault, input);
	if (!input)
		return (false);
	tokenizer(minivault);
	return (check_syntax(minivault));
}
