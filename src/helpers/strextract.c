
#include "minishell.h"

// TODO: PUT THIS SOMEWHERE ELSE
void	print_vector(char **split)
{
	int	i;	
	i = 0;

	while (split[i])
	{
		printf("%d: %s\n", i, split[i]);
		i++;
	}
}


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
		if (is_double_quote(*input) == true && inside_single_quotes == false)
			inside_double_quotes = !inside_double_quotes;
		else if (is_single_quote(*input) == true && inside_double_quotes == false)
			inside_single_quotes = !inside_single_quotes;
		if (is_space(*input) && inside_double_quotes == false && inside_single_quotes == false)
			*(dst++) = '!' ;
		else 
			*(dst++) = *input;
		input++;
	}
	*dst = '\0';
	if (inside_double_quotes || inside_single_quotes == true)
	{
		if (inside_single_quotes)
			ft_putendl_fd("Single quotes not closed.", 2);
		if (inside_double_quotes)
		free (modified);
			ft_putendl_fd("Double quotes not closed.", 2);
		return (NULL);
	}
	return (modified);
}

char	*isolate_quotes(char *input)
{
	char 	*modified;
	int		i;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + 1);
	if (!modified)
		return (NULL);
	i = 0;
	while (input && *input)
	{
		if (is_double_quote(*input) == true && inside_single_quotes == false)
			inside_double_quotes = !inside_double_quotes;
		else if (is_single_quote(*input) == true && inside_double_quotes == false)
			inside_single_quotes = !inside_single_quotes;
		if ((is_single_quote(*input) && inside_single_quotes == true && inside_double_quotes == false) || \
			(is_double_quote(*input) && inside_double_quotes == true && inside_single_quotes == false))
		{
			modified[i++] = '!';
			modified[i++] = *input;
		}
		else if ((is_single_quote(*input) && inside_single_quotes == false && inside_double_quotes == false) || \
				(is_double_quote(*input) && inside_double_quotes == false && inside_single_quotes == false))
		{
			modified[i++] = *input;
			modified[i++] = '!';
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
	char 	*modified;
	int 	i;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	modified = (char *)malloc(2 * (ft_strlen(input) * sizeof(char)) + 1);
	if (!modified)
		return (NULL);
	i = 0;
    while (input && *input)
	{
		if (is_double_quote(*input) == true && inside_single_quotes == false)
			inside_double_quotes = !inside_double_quotes;
		else if (is_single_quote(*input) == true && inside_double_quotes == false)
			inside_single_quotes = !inside_single_quotes;
        if (*input == target && inside_double_quotes == false && inside_single_quotes == false)
		{
            modified[i++] = '!';
            modified[i++] = *input;
            modified[i++] = '!';
        } 
		else 
            modified[i++] = *input;
        input++;
    }
    modified[i] = '\0';
    return (modified);
}

void    strextract(t_minivault *minivault, char *input)
{
	input = remove_spaces(input);
	input = isolate_quotes(input);
	input = isolate_char(input, '|');
	input = isolate_char(input, '&');
	input = isolate_char(input, ';');
	input = isolate_char(input, '(');
	input = isolate_char(input, ')');
	input = isolate_char(input, '<');
	input = isolate_char(input, '>');
	printf(RED"------------INPUT-----------\n%s\n", input);
	minivault->input = ft_split(input, '!');
	printf("------------OUTPUT------------\n");
	print_vector(minivault->input);
	printf(RESET_COLOR);
	free(input);
	return ;
}