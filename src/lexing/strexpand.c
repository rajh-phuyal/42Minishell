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
	char	temp;
	char	*value;
	char	*suffix;

	temp = 0;
	value = NULL;
	suffix = get_suffix(iter + ((*iter == '?') || (!*(iter + 1))));
	if (data->pos && *(data->pos + 1) == PREVEXITSTAT[FIRST_ELEM])
		value = get_env(minivault, PREVEXITSTAT);
	else if (data->pos)
	{
		temp = *(iter) * (*(iter + 1) > 0);
		*iter = (*iter) * !(*(iter + 1) > 0);
		value = get_env(minivault, data->pos + 1);
	}
	if (value)
	{
		built = update_built(built, value, *iter, data->pos);
		built = exe_concat(built, built, suffix, NULL);
	}
	else if (suffix && *(iter + 1) && !built)
		built = exe_concat(built, suffix, NULL);
	free(suffix);
	if (temp)
		*iter = temp;
	return (built);
}

static char	*alchemy(t_minivault *minivault, t_strexp *data, char *iter)
{
	char	*_built;

	_built = NULL;
	while (iter && *iter)
	{
		if (!*(iter + 1) || (!ft_isalnum(*iter) && \
			*iter != '_'))
		{
			_built = process_iter(minivault, data, iter, _built);
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
			if (!*(curr + 1) || *(curr + 1) == 39 || *(curr + 1) == 34)
				break ;
			_put_end_break(curr + 1, data);
			if (data->expandable)
			{
				data->pos = curr;
				_magic = alchemy(minivault, data, curr + 1);
				if (!_magic)
					break ;
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
