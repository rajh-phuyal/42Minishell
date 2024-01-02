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
	else
		_single = false;
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

static	char	*_concat(char *dummy, ...)
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
	char	*end;
	char	*value;
	char	*_prefix;

	end = start;
	while (end && *(end + 1))
		end++;
	if (_cache(false, true) && *(start + 1) != PREVEXITSTAT[FIRST_ELEM])
		*(end - (_exp_validator("", true))) = '\0';
	_prefix = "";
	value = get_env(minivault, start);
	if (value || (*start == PREVEXITSTAT[FIRST_ELEM]))
	{
		*(start - (1 + (_cache(false, true)) + \
				(_exp_validator("", true)))) = '\0';
		if (*start == PREVEXITSTAT[FIRST_ELEM])
		{
			_prefix = (start + 1);
			value = get_env(minivault, PREVEXITSTAT);
		}
		if (_exp_validator("", true))
			return (_concat("", str, "''", value, _prefix, "''", NULL));
		return (_concat("", str, value, _prefix, NULL));
	}
	else
		return (_concat("", PLACEHOLDER, NULL));
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
				if (!*(iter + 1))
					break ;
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
