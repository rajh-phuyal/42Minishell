
#include "minishell.h"


/* syntax errors
 ! ERROR 1
 ? Command: |
 ! ERROR: bash: syntax error near unexpected token `|'
 ------------------------------------------------------------------------------------------------------------------
 ! ERROR 2
 ? Command: | |
 ! ERROR: bash: syntax error near unexpected token `|'
 ------------------------------------------------------------------------------------------------------------------
 ! ERROR 3
 ? Command: <
 ! ERROR: bash: syntax error near unexpected token `newline'
------------------------------------------------------------------------------------------------------------------
 ! ERROR 3
 ? Command: >
 ! ERROR: bash: syntax error near unexpected token `newline'
 ------------------------------------------------------------------------------------------------------------------
 ! ERROR 3
 ? Command: >>
 ! ERROR: bash: syntax error near unexpected token `newline'
 ------------------------------------------------------------------------------------------------------------------
 ! ERROR 3
 ? Command: <<
 ! ERROR: bash: syntax error near unexpected token `newline'
 ------------------------------------------------------------------------------------------------------------------
 ? Command: < file
 * If the file "file" exists, nothing happens, and the prompt returns.
 * If the file "file" does not exist, an error is printed.
 ! ERROR: bash: file: No such file or directory
 ------------------------------------------------------------------------------------------------------------------
 ? Command: > file
 * If the file "file" does not exist, it will be created.
 * If the file "file" already exists, its contents will be replaced with nothing (i.e., the file will be emptied).
 ------------------------------------------------------------------------------------------------------------------
 ? Command: >> file
 * If the file "file" does not exist, it will be created.
 * If the file "file" already exists, the existing content won't be modified.
 ------------------------------------------------------------------------------------------------------------------

*/

void	check_syntax(t_minivault *minivault)
{
	t_token *current;

	if (!minivault->tokens)
		return ;
	current = minivault->tokens;
	if (current->type == PIPE && current->next == NULL)
	{
		error(minivault, FAILURE, "syntax error near unexpected token", "`|'");
		return ;
	}
	while (current)
	{
		if (current && current->type == REDIRECTION && current->next == NULL)
		{
			error(minivault, FAILURE, "syntax error near unexpected token", "`|'");
			return ;
		}
		if (current && current->next && current->type == REDIRECTION && current->next->type == REDIRECTION)
		{
			// ! ERROR SOMETHING
			exit(1);
			return ;
		}
		if (current && current->type == PIPE && current->next == NULL)
		{
			// command: cmd |
			// dont know if the prompt should return or should just print error
			exit(1);
			return ;
		}
		if (current && current->next && current->type == PIPE && current->next->type == PIPE)
		{
			error(minivault, FAILURE, "syntax error near unexpected token", "`|'");
			return ;
		}
		current = current->next;
	}
}

/* atempting to create tokens based on the received input str for the readline */
void	lexer(t_minivault *minivault, char *input)
{
	if (!input)
		return ;
	strextract(minivault, input);
	tokenizer(minivault, 0);
	check_syntax(minivault);
	// _export(minivault, NULL, NULL);
	// _env(minivault, NULL, NULL);
	// _unset(minivault, vector);
	// _cd(minivault, NULL);
	// _pwd(minivault);
	// _echo(minivault, NULL);
	// remove_quotes(minivault);
}
