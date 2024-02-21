#include "minishell.h"

int	ft_abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '"');
}

bool	is_space(char c)
{
	return (c == '\t' || c == ' ' || c == '\n' || c == '\v');
}
