#include "minishell.h"

char	*exe_concat(char *prev, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, prev);
	_built = concat_all(args);
	va_end(args);
	if (prev)
		free(prev);
	prev = NULL;
	return (_built);
}

bool	unpack_var(t_strexp *data, bool quoted, bool singleq, bool expandable)
{
	data->quoted = quoted;
	data->singleq = singleq;
	data->expandable = expandable;
	return (expandable);
}

char	*get_suffix(char *pos)
{
	char	temp;
	char	*start;
	char	*suffix;

	suffix = NULL;
	start = pos;
	temp = '\0';
	while (pos && *pos)
	{
		if (!*(pos + 1) || *pos == DOLLAR)
		{
			if (*(pos + 1))
			{
				temp = *pos;
				*pos = '\0';
			}
			suffix = exe_concat(NULL, start, NULL);
			if (temp)
				*pos = temp;
			break ;
		}
		pos++;
	}
	if (!suffix)
		suffix = exe_concat(NULL, start, NULL);
	return (suffix);
}

bool	_check_heredoc_deli(char *str, char **vector)
{
	if (vector && *vector == str)
		return (true);
	while (vector && *vector)
	{
		if (!ft_strncmp(*vector, "<<", ft_strlen(*vector)))
		{
			if (vector && *(vector + 1) == str)
				return (false);
		}
		vector++;
	}
	return (true);
}
