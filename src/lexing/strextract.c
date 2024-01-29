
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
 * @param input is the input string
 * @param separator the char used to replace the spaces
*/
char	*remove_spaces(char *input, char separator)
{
	char	*modified;
	char	*dst;
	char	*temp;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	dst = modified;
	temp = input;
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
		if (temp)
			free(temp);
		free(modified);
		return (NULL);
	}
	if (temp)
		free(temp);
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
	char	*temp;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	temp = input;
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
	if (temp)
		free(temp);
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
	char	*temp;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) + 1) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	temp = input;
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
	if (temp)
		free(temp);
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
	char	*temp;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	if(!input)
		return (NULL);
	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + sizeof(char)); // + 1 should be + sizeof(char) ?
	if (!modified)
		return (NULL);
	i = 0;
	temp = input;
	while (input && *input)
	{
		toggle_quotes(*input, &inside_double_quotes, &inside_single_quotes);
		if (*input == target[FIRST_ELEM] && *(input + 1) == target[SECOND_ELEM] \
			&& inside_double_quotes == false && inside_single_quotes == false)
		{
			modified[i++] = separator;
			modified[i++] = (*(input++)) * -1;
			modified[i++] = (*(input++)) * -1;
			modified[i++] = separator;
		}
		else
			modified[i++] = *(input++);
	}
	modified[i] = '\0';
	if (temp)
		free(temp);
	return (modified);
}

static char *strip_double_quotes(char *input)
{
    char *new_str;

    if (!input || ft_strlen(input) != 2)
        return (input);
    if ((is_single_quote(input[0]) && is_single_quote(input[1])) ||
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

static char *clean_quotes(char *input)
{
    int     len;
    int     i;
    int     j;
    char    *cleaned;
    bool    in_double_quotes;
    bool    in_single_quotes;

    if (!input || (len = strlen(input)) < 2)
        return (input);
    in_double_quotes = false;
    in_single_quotes = false;
    cleaned = malloc(len + 1);
    if (!cleaned)
        return (NULL);
    j = 0;
    i = -1;
    while (++i < len)
    {
        toggle_quotes(input[i], &in_double_quotes, &in_single_quotes);
        if ((!is_single_quote(input[i]) && !is_double_quote(input[i])) ||
            (in_single_quotes && is_double_quote(input[i])) ||
            (in_double_quotes && is_single_quote(input[i])))
            cleaned[j++] = input[i];
    }
    cleaned[j] = '\0';
    return (cleaned);
}

void process_strings(char ***input)
{
    char    *temp;
    char    *temp2;
    int     i;

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
        temp2 = clean_quotes((*input)[i]);
        if (temp2 != (*input)[i])
        {
            free((*input)[i]);
            (*input)[i] = temp2;
        }
        i++;
    }
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
	
	// printf("input before                   : %s\n", input);
	input = remove_spaces(input, '\31');
	// printf("input after remove_spaces      : %s\n", input);
	if (!input)
		return ;
	// input = isolate_quotes(input, '_');
	// if (!input)
	// 	return ;
	// printf("input after isolate_quotes     : %s\n", input);
	input = isolate_compound(input, ">>", '\31');
	// printf("input after isolate_compound >>: %s\n", input);
	if (!input)
		return ;
	input = isolate_compound(input, "<<", '\31');
	// printf("input after isolate_compound <<: %s\n", input);
	if (!input)
		return ;
	input = isolate_char(input, '|', '\31');
	// printf("input after isolate_char |     : %s\n", input);
	if (!input)
		return ;
	input = isolate_char(input, '<', '\31');
	// printf("input after isolate_char <     : %s\n", input);
	if (!input)
		return ;
	input = isolate_char(input, '>', '\31');
	if (!input)
		return ;
	char *temp = input;
	while (temp && *temp)
	{
		if (*temp < 0)
			*temp = (*temp) * -1;
		temp++;
	}
	if (input)
		minivault->input = ft_split(input, '\31');
	process_strings(&minivault->input);
	strexpand(minivault, minivault->input);
	free(input);
}
