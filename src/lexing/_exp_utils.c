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

bool	_is_heredoc_deli(char *str, char **vector)
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
