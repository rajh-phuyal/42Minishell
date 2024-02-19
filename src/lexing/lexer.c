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

bool	check_open_quotes(char *input)
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
		if (inside_squotes) // ! change this to error
			ft_putendl_fd("Single quotes not closed.", 2);
		else if (inside_dquotes) // ! change this to error
			ft_putendl_fd("Double quotes not closed.", 2);
		return (false);
	}
	return (true);
}

static char	*strip_double_quotes(char *input)
{
	char	*new_str;

	if (!input || ft_strlen(input) != 2)
		return (input);
	if ((is_single_quote(input[0]) && is_single_quote(input[1])) || \
		(is_double_quote(input[0]) && is_double_quote(input[1])))
	{
		new_str = malloc(2);
		if (new_str)
		{
			new_str[0] = '\31';
			new_str[1] = '\0';
			return (new_str);
		}
	}
	return (input);
}

bool	str_is_quoted(const char *str)
{
	int	len;

	if (!str || !*str)
		return (false);
	len = ft_strlen(str);
	if ((is_double_quote(str[0]) && is_double_quote(str[len - 1])) || \
		(is_single_quote(str[0]) && is_single_quote(str[len - 1])))
		return (true);
	return (false);
}

static char	*clean_quotes(char *input)
{
	char	*modified;
	char	*result;
	size_t	i;
	size_t	j;

	if (ft_strlen(input) < 2 || str_is_quoted(input))
		return (input);
	modified = ft_calloc(1, ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (!is_single_quote(input[i]) && !is_double_quote(input[i]))
			modified[j++] = input[i];
		i++;
	}
	result = modified; // Keep the original pointer for return
	return (result);
}

void	process_strings(char ***input)
{
	char	*temp;
	int		i;

	if (!input || !*input)
		return ;
	i = 0;
	while ((*input)[i])
	{
		temp = strip_double_quotes((*input)[i]);
		if (temp != (*input)[i])
		{
			free((*input)[i]);
			(*input)[i] = temp;
		}
		temp = clean_quotes((*input)[i]);
		if (temp != (*input)[i])
		{
			free((*input)[i]);
			(*input)[i] = temp;
		}
		i++;
	}
}

/* atempting to create tokens based on the
received input str for the readline */
bool	lexer(t_minivault *minivault, char *line)
{
	if (!check_open_quotes(line))
		return (false);
	line = strextract(line);
	if (line)
		minivault->input = ft_split(line, '\31');
	process_strings(&minivault->input);
	strexpand(minivault, minivault->input);
	free(line);
	tokenizer(minivault);
	return (check_syntax(minivault));
}
