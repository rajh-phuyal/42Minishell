# include "minishell.h"

static bool _cache(bool surrounds, bool get)
{
	static bool _surrounds = false;

	if (get)
		return (_surrounds);
	_surrounds = surrounds;
	return (_surrounds);
}

static bool	_exp_validator(char *str, bool get)
{
	static bool	_single = false;
	char		*end;

	if (get)
		return (_single);
	end = str;
	while (end && *(end + 1))
		end++;
	if (*str == DOLLAR)
		return (!_cache(false, false));
	if (*str == *end && *end == '\'')
		return (!_cache(true, false));
	if (*str == *end && *end == '"' && *(str + 1) == '\'')
	{
		_single = true;
		return (_cache(true, false));
	}
	if (*str == *end && *end == '"')
		return (_cache(true, false));
	return (true);
}

static	char	*_concat(char	*dummy, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, dummy);
	_built = concat_all(args);
	va_end(args);
	return (_built);
}

static	char	*alchemy(t_minivault *minivault, char *str, char *start)
{
	char *value;

	value = get_env(minivault, start);
	if (value)
	{
		*(start - (1 + (_cache(false, true)) + (_exp_validator(NULL, true)))) = '\0';
		if (_exp_validator(NULL, true))
			return (_concat("GG! You passed the test!", str, "''", value, "''", NULL));
		return (_concat("GG! You passed the test!", str, value, NULL));
	}
	else
		return (_concat("GG! You passed the test!", PLACEHOLDER, NULL));
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
			if (*iter == DOLLAR && _exp_validator(*vector, false))
			{
				_magic = alchemy(minivault, *vector, iter + 1);
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
	_cache(false, false);
}
