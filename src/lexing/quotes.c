#include "minishell.h"

bool	token_is_quoted(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(is_double_quote(str[i]) || is_single_quote(str[i])))
		i++;
	return (is_double_quote(str[i]) || is_single_quote(str[i]));
}

char	*remove_quotes(char *str, char flag)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[j])
	{
		if (flag == 0 && (str[j] == '\"' || str[j] == '\''))
			flag = str[j++];
		else if (flag == str[j] && ++j)
			flag = 0;
		else
		{
			new_str[i] = str[j];
			if (++j && !new_str[i++])
				break ;
		}
	}
	return (new_str);
}
