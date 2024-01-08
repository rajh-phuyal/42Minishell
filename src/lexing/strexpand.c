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

static	void	_put_end_break(char *start)
{
	char	*end;

	end = start;
	while (end && *(end + 1))
		end++;
	if (_cache(false, true) && *(start + 1) != PREVEXITSTAT[FIRST_ELEM])
		*(end - (_exp_validator("", true))) = '\0';
}

static	char	*alchemy(t_minivault *minivault, char *str, char *start)
{
	char	*value;
	char	*_prefix;

	_prefix = "";
	_put_end_break(start);
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
		else
		{

		}
		if (_exp_validator("", true))
			return (exe_concat("", str, "''", value, _prefix, "''", NULL));
		return (exe_concat("", str, value, _prefix, NULL));
	}
	else
		return (exe_concat("", PLACEHOLDER, NULL));
}

// void    strexpand(t_minivault *minivault, char **vector)
// {
// 	char	*iter;
// 	char	*_magic;

// 	while (vector && *vector)
// 	{
// 		iter = *vector;
// 		printf("current vector: %s\n", *vector);
// 		while (iter && *iter)
// 		{
// 			if (*iter == DOLLAR && _exp_validator(*vector, false))
// 			{
// 				if (!*(iter + 1))
// 					break ;
// 				_magic = alchemy(minivault, *vector, iter + 1);
// 				if (!_magic)
// 					continue ;
// 				free(*vector);
// 				*vector = _magic;
// 				continue ;
// 			}
// 			printf("current iter char: %c\n", *iter);
// 			iter++;
// 		}
// 		vector++;
// 	}
// 	_cache(false, false);
// }

// void    strexpand(t_minivault *minivault, char **vector)
// {
// 	char	*iter;
// 	char	*_magic;

// 	while (vector && *vector)
// 	{
// 		iter = *vector;
// 		while (iter && *iter)
// 		{
// 			if (*iter == DOLLAR && _exp_validator(*vector, false))
// 			{
// 				if (!*(iter + 1))
// 					break ;
// 				_magic = alchemy(minivault, *vector, iter + 1);
// 				if (!_magic)
// 					continue ;
// 				free(*vector);
// 				*vector = _magic;
// 				continue ;
// 			}
// 			iter++;
// 		}
// 		vector++;
// 	}
// 	_cache(false, false);
// }

// figure out the quotes suitation around the dollar
// go through the string
	// if a dollar is found
		// if no char after the dollar
			// terminate string with the dollar
		// else go through each character
			// if dollar is found and no value yet
				// save the position of the dollar (the $ and the character after the dollar are removed)
			// else dollar is found and value is found
				// replace the $key with the value
			// continue until the end of the string

void	_cleaner(t_strexp *data)
{
	data->quotes = false;
	data->singleq = false;
	data->isHereDoc = false;
	data->expandable = false;
}

static	void	_exp_validator(char *str, t_strexp *data)
{
	char		*end;

	end = str;
	while (end && *(end + 1))
		end++;
	if (*str == DOLLAR)
		data->expandable = true;
	else if (*str == *end && *end == '\'')
		data->quoted = true;
	else if (*str == *end && *end == '"' && *(str + 1) == '\'')
	{
		data->singleq = true;
		data->quoted = true;
		data->expandable = true;
	}
	else if (*str == *end && *end == '"')
	{
		data->quoted = true;
		data->expandable = true;
	}
}

static	void	_put_end_break(char *start, t_strexp *data)
{
	char	*end;

	end = start;
	while (end && *(end + 1))
		end++;
	if (data->quoted && *(start + 1) != PREVEXITSTAT[FIRST_ELEM])
		*(end - (data->singleq)) = '\0';
}

static	char	*alchemy(t_minivault *minivault, t_strexp *data, \
							char *str, char *start)
{
	*(start - (1 + (data->quoted) + (data->singleq))) = '\0'; // null the $
	while (start && *start)
	{
		value = get_env(start);
		if (value)
			exe_concat("", str, )
	}
}

// str$PATH$?$nonono

void	_check_heredoc_deli(char *str, char **vector, t_strexp *data)
{
	if (vector && *vector == str)
	{
		data->expandable = true;
		return ;
	}
	while (vector && *vector)
	{
		if (!ft_strncmp(*vector, "<<", ft_strlen(*vector)))
		{
			if (vector && (vector + 1) != str)
				data->expandable = true;
		}
	}
}

void	strexpand(t_minivault *minivault, char **vector)
{
	t_strexp	data;
	char		*s_iter;
	char		**v_iter;

	v_iter = vector;
	while (v_iter && *v_iter)
	{
		s_iter = *v_iter;
		_cleaner(&data);
		_exp_validator(s_iter, &data);
		_check_heredoc_deli(s_iter, vector, &data);
		if (data->expandable)
		{
			while (s_iter && *s_iter)
			{
				if (*s_iter == DOLLAR)
				{
					if (!*(s_iter + 1))
						break ;
					_magic = alchemy(minivault, &data, *v_iter, s_iter + 1);
					if (!_magic)
						break ;
					free(*v_iter);
					*v_iter = _magic;
					break ;
				}
				s_iter++;
			}
		}
		v_iter++;
	}
}