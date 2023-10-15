
#include "minishell.h"

bool	is_space(char c)
{
	return (c == '\t' || c == ' ' || c == '\n' || c == '\v');
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*strmodify(char* input)
{
    char		*modified;
	char		*dst;
	bool		inside_quotes = false;

	modified = malloc(strlen(input) + 1);
	if (!modified)
		return (NULL);

	dst = modified;
    while (*input) 
	{
        if (is_quote(*input)) 
            inside_quotes = !inside_quotes;
        if (!inside_quotes && is_space(*input))
		{
			if (!is_space(*(input - 1)))
				*(dst++) = '\x1F';
        } 
		else 
            *(dst++) = *input;
        input++;
    }

    *dst = '\0';
    return (modified);
}

// prints the splitted string with index
void	print_split(char **split)
{
	int	i;	
	i = 0;

	while (split[i])
	{
		printf("%d: %s\n", i, split[i]);
		i++;
	}
}

void    strextract(t_minivault *minivault, char *input)
{
	input = strmodify(input); // cleaning spaces
	minivault->input = ft_split(input, '\x1F'); // \x1F is an UNIT SEPARATOR 31 in ascii
	free(input);
}