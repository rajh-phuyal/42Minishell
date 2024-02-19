#include "minishell.h"

/* syntax errors
 ! ERROR 1
 ? Command: |
 ! ERROR: bash: syntax error near unexpected token `|'
 -------------------------------------------------------------------------
 ! ERROR 2
 ? Command: | |
 ! ERROR: bash: syntax error near unexpected token `|'
 -------------------------------------------------------------------------
 ! ERROR 3
 ? Command: <
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------
 ! ERROR 3
 ? Command: >
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------
 ! ERROR 3
 ? Command: >>
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------
 ! ERROR 3
 ? Command: <<
 ! ERROR: bash: syntax error near unexpected token `newline'
 -------------------------------------------------------------------------
 ? Command: < file
 * If the file "file" exists, nothing happens, and the prompt returns.
 * If the file "file" does not exist, an error is printed.
 ! ERROR: bash: file: No such file or directory
 -------------------------------------------------------------------------
 ? Command: > file
 * If the file "file" does not exist, it will be created.
 * If the file "file" already exists, its contents will be
 * replaced with nothing (i.e., the file will be emptied).
 -------------------------------------------------------------------------
 ? Command: >> file
 * If the file "file" does not exist, it will be created.
 * If the file "file" already exists,
 * the existing content won't be modified.
 -------------------------------------------------------------------------
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
		if (current && current->next && \
			current->type == REDIRECTION && current->next->type == PIPE)
		{
			error(minivault, FAILURE, true, \
			"syntax error near unexpected token", "`|'", NULL);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	check_open_quotes(t_minivault *minivault, char *input)
{
	bool	inside_dquotes;
	bool	inside_squotes;

	inside_dquotes = false;
	inside_squotes = false;
	if (!input)
		return (false);
	while (input && *input)
	{
		toggle_quotes(*input, &inside_dquotes, &inside_squotes);
		input++;
	}
	if (inside_dquotes || inside_squotes)
	{
		if (inside_squotes)
			error(minivault, QUOTESEXIT, true, "Single quotes not closed.", NULL);
		else if (inside_dquotes)
			error(minivault, QUOTESEXIT, true, "Double quotes not closed.", NULL);
		return (false);
	}
	return (true);
}

/* attempting to create tokens based on the
received input str for the readline */
bool	lexer(t_minivault *minivault, char *line)
{
	if (!check_open_quotes(minivault, line))
		return (false);
	line = strextract(line);
	if (line)
		minivault->input = ft_split(line, '\31');
	strexpand(minivault, minivault->input);
	free(line);
	tokenizer(minivault);
	return (check_syntax(minivault));
}
