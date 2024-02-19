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
 * @brief 	if one or multiple spaces are found outside
 * 			of a quotes, they are replaced by the separator
 * 			E.g.: hello        world "   again"
 * 				hello\world\"   again" <- where \ is the separator
 * @param input is the input string
 * @param separator the char used to replace the spaces
*/
char	*remove_spaces(char *input, char separator)
{
	t_inside	inside;
	char		*modified;
	char		*dst;
	char		*temp;

	inside = (t_inside){false, false};
	modified = ft_calloc(1, strlen(input) + 1);
	if (!modified)
		return (NULL);
	dst = modified;
	temp = input;
	while (*input)
	{
		toggle_quotes(*input, &inside.dquotes, &inside.squotes);
		if (is_space(*input) && !inside.dquotes && !inside.squotes)
		{
			if (dst == modified || !is_space(*(dst - 1)))
				*(dst++) = separator;
		}
		else
			*(dst++) = *input;
		input++;
	}
	free(temp);
	return (modified);
}

/**
 * * isolate_char
 * @brief	if the target char is found inside the
 * 			input string (outside of single or double quotes)
 * 			it is isolated by the separator. E.g.: hello>1 becomes hello > 1
 * @param input is the input string
 * @param target is the target char
 * @param separator the char used to isolate the target in the input
*/

char	*isolate_char(char *input, char target, char separator, int i)
{
	t_inside	inside;
	char		*modified;
	char		*temp;

	inside = (t_inside){false, false};
	modified = (char *)ft_calloc(2, ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	temp = input;
	while (input && *input)
	{
		toggle_quotes(*input, &inside.dquotes, &inside.squotes);
		if (*input == target && !inside.dquotes && !inside.squotes)
		{
			modified[i++] = separator;
			modified[i++] = *input;
			modified[i++] = separator;
		}
		else
			modified[i++] = *input;
		input++;
	}
	free(temp);
	return (modified);
}

/**
 * * isolate_compund
 * @brief	if the target string is found inside the
 * 			input string (outside of single or double quotes)
 * 			it is isolated by the separator. E.g.: hello>>1 becomes hello >> 1
 * @param input is the input string
 * @param target is the target string
 * @param separator the char used to isolate the target in the input
 * ! FIX: the only chars "used" from the target string are the first two
*/
static char	*isolate_compound(char *input, char *target, char separator, int i)
{
	t_inside	inside;
	char		*temp;
	char		*modified;

	inside = (t_inside){false, false};
	modified = (char *)ft_calloc(2, ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	temp = input;
	while (input && *input)
	{
		toggle_quotes(*input, &inside.dquotes, &inside.squotes);
		if (*input == target[FIRST_ELEM] && *(input + 1) == target[SECOND_ELEM] \
			&& inside.dquotes == false && inside.squotes == false)
		{
			modified[i++] = separator;
			modified[i++] = (*(input++)) * -1;
			modified[i++] = (*(input++)) * -1;
			modified[i++] = separator;
		}
		else
			modified[i++] = *(input++);
	}
	free(temp);
	return (modified);
}

/**
 * * strextract
 * @brief		spaces, isolates special chars and
 * 				splits the input string into a vector 2D ARRAY
 * @param 		minivault is a pointer to the "general" structure
 * @param		input is the input string
*/

int	ft_abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

char	*strextract(char *line)
{
	char	*temp;

	line = remove_spaces(line, '\31');
	if (!line)
		return (NULL);
	line = isolate_compound(line, ">>", '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_compound(line, "<<", '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_char(line, '|', '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_char(line, '<', '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_char(line, '>', '\31', 0);
	temp = line;
	while (temp && *temp)
	{
		*temp = ft_abs(*temp);
		temp++;
	}
	return (line);
}
