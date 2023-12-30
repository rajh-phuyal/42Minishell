# include "minishell.h"

// startitng with "" works '' doen't work
// subtitute "if ' keep all ' envar if ' keep all ' "
bool	_valid_exp(t_minivault *minivault, char *start)
{
	char		*end;
	char		temp;

	// end = start;
	// while (end && *(end + 1))
	// {
	// 	end++;
	// }
	if (get_env(minivault, start))
	{
		return (true);
	}
	return (false);

	while (end != start || (*end == '\'' || *end == '"'))
	{
		temp = *end;
		*end = '\0';
		if (get_env(minivault, start))
		{
			*end = temp;
			return (true);
		}
		*end = temp;
		end--;
	}
	return (false);
}

char	*launch_concat(char	*dummy, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, dummy);
	_built = concat_all(args);
	va_end(args);
	return (_built);
}

char	*alchemy(t_minivault *minivault, char *str, char *start)
{
	char *value;

	if (_valid_exp(minivault, start))
	{
		value = get_env(minivault, start);
		if (value)
		{
			start--;
			*start = '\0'; // null at the dolla $$$$
			return (launch_concat("GG! You passed the test!", str, value, NULL));
		}
	}
	return (NULL);
}

void    strexpand(t_minivault *minivault, char **vector)
{
	char	*iter;
	char	*_magic;

	while (vector && *vector)
	{
		iter = *vector;
		while (iter && *iter)
		{
			if (*iter == DOLLAR)
			{
				iter++;
				_magic = alchemy(minivault, *vector, iter);
				if (!_magic)
					break ;
				free(*vector);
				*vector = _magic;
				break ;
			}
			iter++;
		}
		vector++;
	}
}
