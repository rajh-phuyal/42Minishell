#include "minishell.h"

static bool	_exp_validator(char *str, char *end, t_strexp *data)
{
	if (!_has_expander(str))
		return (unpack_var(data, false, false, false));
	while (end && *(end + 1))
		end++;
	while (str && *str && *str != DOLLAR && *str != 39 && *str != 34)
		str++;
	while (end != str && *end != DOLLAR && *end != 39 && *end != 34)
		end--;
	if (*str == DOLLAR && *end == DOLLAR)
		return (unpack_var(data, false, false, true));
	if (*str == *end && *str == 39 && *(str + 1) == 34)
		return (unpack_var(data, true, true, false));
	else if (*str == *end && *end == 39)
		return (unpack_var(data, false, true, false));
	if (*str == *end && *end == 34 && *(str + 1) == 39)
		return (unpack_var(data, true, true, true));
	else if (*str == *end && *end == 34)
		return (unpack_var(data, true, false, true));
	return (unpack_var(data, false, false, false));
}

static char	*process_iter(t_minivault *minivault, t_strexp *data, char *iter,
		char *built)
{
	char	*value;

	value = NULL;
	if (data->pos && *(data->pos + 1) == PREVEXITSTAT[FIRST_ELEM])
		value = get_env(minivault, PREVEXITSTAT);
	else if (data->pos)
		value = get_env(minivault, data->pos + 1);
	if (value)
		built = update_built(built, value, *iter, data->pos);
	return (built);
}

static char	*alchemy(t_minivault *minivault, t_strexp *data, char *iter)
{
	char	temp;
	char	*_built;

	temp = '\0';
	_built = NULL;
	while (iter && *iter)
	{
		if (!*(iter + 1) || *iter == DOLLAR || *iter == 32 || *iter == 33
			|| *iter == 34 || *iter == 92 || *iter == 47)
		{
			temp = *iter * (*(iter + 1) > 0);
			*iter = (*iter) * !(*(iter + 1) > 0);
			_built = process_iter(minivault, data, iter, _built);
			if (temp)
				*iter = temp;
			if (*iter == DOLLAR)
				data->pos = iter;
			else
				data->pos = NULL;
		}
		iter++;
	}
	return (build_or_not_build(_built, data));
}

void	process_string(char *curr, char **v_iter, t_minivault *minivault,
		t_strexp *data)
{
	char	*_magic;

	_magic = NULL;
	while (curr && *curr)
	{
		if (*curr == DOLLAR)
		{
			if (!*(curr + 1))
				break ;
			_put_end_break(curr + 1, data);
			if (data->expandable)
			{
				_magic = alchemy(minivault, data, curr);
				if (!_magic)
					break ;
				*(curr - (data->quoted + data->singleq)) = '\0';
			}
			finilize_magic_str(v_iter, curr, _magic, data);
			break ;
		}
		curr++;
	}
}

void	strexpand(t_minivault *minivault, char **vector)
{
	char		**v_iter;
	char		*s_iter;
	t_strexp	data;

	v_iter = vector;
	while (v_iter && *v_iter)
	{
		s_iter = *v_iter;
		_cleaner(&data);
		_exp_validator(s_iter, s_iter, &data);
		if (_is_heredoc_deli(s_iter, vector))
			process_string(s_iter, v_iter, minivault, &data);
		v_iter++;
	}
}
