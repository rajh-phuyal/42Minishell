
#include "minishell.h"

static char	*strip_double_quotes(char *input)
{
	char	*new_str;

	if (!input || ft_strlen(input) != 2)
		return (NULL);
	if ((is_single_quote(input[0]) && is_single_quote(input[1]))
		|| (is_double_quote(input[0]) && is_double_quote(input[1])))
	{
		free(input);
		new_str = malloc(2);
		if (new_str)
		{
			new_str[0] = ' ';
			new_str[1] = '\0';
			return (new_str);
		}
	}
	return (NULL);
}

bool	str_is_quoted(const char *str)
{
	int	len;

	if (!str || !*str)
		return (false);
	len = ft_strlen(str);
	if ((is_double_quote(str[0]) && is_double_quote(str[len - 1]))
		|| (is_single_quote(str[0]) && is_single_quote(str[len - 1])))
		return (true);
	return (false);
}

// static char	*clean_quotes(char *input)
// {
// 	char	*modified;
// 	char	*result;
// 	size_t	i;
// 	size_t	j;

// 	if (ft_strlen(input) < 2) // || str_is_quoted(input)
// 		return (input);
// 	modified = ft_calloc(1, ft_strlen(input) + 1);
// 	if (!modified)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (input[i])
// 	{
// 		if (!is_single_quote(input[i]) && !is_double_quote(input[i]))
// 			modified[j++] = input[i];
// 		i++;
// 	}
// 	result = modified;
// 		// Keep the original pointer for return (return (result));
// }

// char	*remove_token_quotes(char *input)
// {
// 	char *temp;

// 	temp = input;
// 	if (input)
// 	{
// 		input = strip_double_quotes(input);
// 		if (input)
// 		{
// 			input = clean_quotes(input);
// 			if (!input)
// 				return (temp);
// 		}
// 	}
// 	return (input);
// }