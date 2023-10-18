
#include "minishell.h"

bool	is_space(char c)
{
	return (c == '\t' || c == ' ' || c == '\n' || c == '\v');
}


bool	is_double_quote(char c)
{
	return (c == '"');
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == ';' || \
			c == '(' || c == ')' || c == '<' || c == '>');
}

void	toggle_quotes(char input, bool *inside_double_quotes, \
								bool *inside_single_quotes)
{
	if (is_double_quote(input) && !(*inside_single_quotes))
		*inside_double_quotes = !(*inside_double_quotes);
	else if (is_single_quote(input) && !(*inside_double_quotes))
		*inside_single_quotes = !(*inside_single_quotes);
}



// modifies spaces (outside of quotes) into UNIT SEPARATOR !
char	*remove_spaces(char *input)
{
	char	*modified;
	char	*dst;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	dst = modified;
	while (input && *input)
	{
		toggle_quotes(*input, &inside_double_quotes, &inside_single_quotes);
		if (is_space(*input) && inside_double_quotes == false && inside_single_quotes == false)
			*(dst++) = '\31';
		else
			*(dst++) = *input;
		input++;
	}
	*dst = '\0';
	if (inside_double_quotes || inside_single_quotes == true)
	{
		if (inside_single_quotes)
			ft_putendl_fd("Single quotes not closed.", 2);
		else if (inside_double_quotes)
			ft_putendl_fd("Double quotes not closed.", 2);
		free (modified);
		return (NULL);
		//TODO : THIS SEGFAULTS cant just return null
	}
	return (modified);
}

char	*isolate_quotes(char *input)
{
	char	*modified;
	int		i;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	while (input && *input)
	{
		toggle_quotes(*input, &inside_double_quotes, &inside_single_quotes);
		if ((is_single_quote(*input) && inside_single_quotes == true && inside_double_quotes == false) || \
			(is_double_quote(*input) && inside_double_quotes == true && inside_single_quotes == false))
		{
			modified[i++] = '\31';
			modified[i++] = *input;
		}
		else if ((is_single_quote(*input) && inside_single_quotes == false && inside_double_quotes == false) || \
				(is_double_quote(*input) && inside_double_quotes == false && inside_single_quotes == false))
		{
			modified[i++] = *input;
			modified[i++] = '\31';
		}
		else
			modified[i++] = *input;
		input++;
	}
	modified[i] = '\0';
	return (modified);
}

char	*isolate_char(char *input, char target)
{
	char	*modified;
	int		i;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	while (input && *input)
	{
		toggle_quotes(*input, &inside_double_quotes, &inside_single_quotes);
		if (*input == target && inside_double_quotes == false \
							&& inside_single_quotes == false)
		{
			modified[i++] = '\31';
			modified[i++] = *input;
			modified[i++] = '\31';
		}
		else
			modified[i++] = *input;
		input++;
	}
	modified[i] = '\0';
	return (modified);
}

char	*isolate_compound(char *input, char *target)
{
	char	*modified;
	int		i;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + 1); // + 1 should be + sizeof(char) ?
	if (!modified)
		return (NULL);
	i = 0;
	while (input && *input)
	{
		toggle_quotes(*input, &inside_double_quotes, &inside_single_quotes);
		if (*input == target[0] && *(input + 1) == target[1] && inside_double_quotes == false && inside_single_quotes == false)
		{
			modified[i++] = '\"';
			modified[i++] = target[0];
			modified[i++] = target[1];
			modified[i++] = '\"';
			input++;
			input++;
		}
		else
		{
			modified[i++] = *input;
			input++;
		}
	}
	modified[i] = '\0';
	return (modified);
}

char 	*isolate_special_chars(char *input)
{
	input = isolate_compound(input, ">>");
	input = isolate_compound(input, "<<");
	input = isolate_char(input, '|');
	input = isolate_char(input, '&');
	input = isolate_char(input, ';');
	input = isolate_char(input, '<');
	input = isolate_char(input, '>');
	return (input);
}

void	strextract(t_minivault *minivault, char *input)
{
	input = remove_spaces(input);
	input = isolate_quotes(input);
	input = isolate_special_chars(input);
	input = isolate_quotes(input);
	printf(YELLOW"------------OUTPUT_STRING-----------\n%s\n", input);
	minivault->input = ft_split(input, '\31');
	printf(RED"------------OUTPUT_VECTOR-----------\n");
	print_vector(minivault->input);
	printf(RESET_COLOR);
	free(input);
}
// TODO: Check how () works. It has the same logic as quotes?

// bash: syntax error near unexpected token `>'