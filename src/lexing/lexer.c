#include "minishell.h"

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
			error(minivault, QUOTESEXIT, true, \
			"Single quotes not closed.", NULL);
		else if (inside_dquotes)
			error(minivault, QUOTESEXIT, true, \
			"Double quotes not closed.", NULL);
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
