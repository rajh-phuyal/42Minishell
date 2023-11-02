
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

/**
 * * remove_spaces
 * @brief 	if one or multiple spaces are found outside of a quotes, they are replaced by the separator
 * 			E.g.: hello        world "   again" -> hello\world\"   again" <- where \ is the separator
 * 			It also checks if there are unclosed quotes in the input string
 * ! FIX: This segfaults in the case of unclosed quotes, can't just return NULL
 * ! If a quote is missing it should return the prompt util the quotes are closed
 * @param input is the input string
 * @param separator the char used to replace the spaces
*/
char	*remove_spaces(char *input, char separator)
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
			*(dst++) = separator;
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
	}
	return (modified);
}

/**
 * * isolate_quotes
 * @brief	a quoted string is found inside of the input string it is isolated by the separator.
 * 			E.g.: hello"world"123 becomes hello "world" 123
 * @param input is the input string
 * @param separator the char used to isolate the quoted string in the input
*/
char	*isolate_quotes(char *input, char separator)
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
			modified[i++] = separator;
			modified[i++] = *input;
		}
		else if ((is_single_quote(*input) && inside_single_quotes == false && inside_double_quotes == false) || \
				(is_double_quote(*input) && inside_double_quotes == false && inside_single_quotes == false))
		{
			modified[i++] = *input;
			modified[i++] = separator;
		}
		else
			modified[i++] = *input;
		input++;
	}
	modified[i] = '\0';
	return (modified);
}

/**
 * * isolate_char
 * @brief	if the target char is found inside the input string (outside of single or double quotes) 
 * 			it is isolated by the separator. E.g.: hello>1 becomes hello > 1
 * @param input is the input string
 * @param target is the target char
 * @param separator the char used to isolate the target in the input
*/
char	*isolate_char(char *input, char target, char separator)
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
			modified[i++] = separator;
			modified[i++] = *input;
			modified[i++] = separator;
		}
		else
			modified[i++] = *input;
		input++;
	}
	modified[i] = '\0';
	return (modified);
}

/**
 * * isolate_compund
 * @brief	if the target string is found inside the input string (outside of single or double quotes) 
 * 			it is isolated by the separator. E.g.: hello>>1 becomes hello >> 1
 * @param input is the input string
 * @param target is the target string
 * @param separator the char used to isolate the target in the input
 * ! FIX: the only chars "used" from the target string are the first two
*/
char	*isolate_compound(char *input, char *target, char separator)
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
		if (*input == target[0] && *(input + 1) == target[1] \
			&& inside_double_quotes == false && inside_single_quotes == false)
		{
			modified[i++] = separator;
			modified[i++] = *(input++);
			modified[i++] = *(input++);
			modified[i++] = separator;
		}
		else
			modified[i++] = *(input++);
	}
	modified[i] = '\0';
	return (modified);
}

/**
 * * strextract 
 * @brief	 spaces, isolates special chars and splits the input string into a vector 2D ARRAY
 * @param minivault is a pointer to the "general" structure
 * @param input is the input string
 * ? Can this be made in a more efficient way
 * TODO: Check how () works. It has the same logic as quotes?
 * TODO: Realloc beffore splitting
 * TODO: ERROR MANAGEMENT like -> bash: syntax error near unexpected token`token'
 * ! FIX: The separator for the isolate compount cant be \", because input: echo ">>" will be the same as echo >>
*/
void	strextract(t_minivault *minivault, char *input)
{
	input = remove_spaces(input, '\31');
	// input = isolate_compound(input, ">>", '\"');
	// input = isolate_compound(input, "<<", '\"');
	input = isolate_char(input, '|', '\31');
	input = isolate_char(input, '&', '\31');
	input = isolate_char(input, ';', '\31');
	input = isolate_char(input, '<', '\31');
	input = isolate_char(input, '>', '\31');
	input = isolate_quotes(input, '\31');
	if (input)
		minivault->input = ft_split(input, '\31');
}
