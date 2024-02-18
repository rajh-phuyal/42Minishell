#include "minishell.h"

static void	_cleaner(t_strexp *data)
{
	data->quoted = false;
	data->singleq = false;
	data->expandable = false;
	data->pos = NULL;
}

static bool	_exp_validator(char *str, t_strexp *data)
{
	char	*end;

	end = str;
	while (end && *(end + 1))
		end++;
	while (end != str && *end != 39 && *end != 34)
		end--;
	while (str && *str && *str != DOLLAR && *str != 39 && *str != 34)
		str++;
	if (*str == DOLLAR && *end == DOLLAR)
		return (unpack_var(data, false, false, true));
	if (*str == *end && *str == 39)
		return (unpack_var(data, true, true, false));
	if (*str == *end && *end == 34 && *(str + 1) == 39)
		return (unpack_var(data, true, true, true));
	else if (*str == *end && *end == 34)
		return (unpack_var(data, true, false, true));
	return (unpack_var(data, false, false, false));
}

static void	_put_end_break(char *start, t_strexp *data)
{
	char	*end;

	end = start;
	while (end && *(end + 1))
		end++;
	if (data->quoted && *(start + 1) != PREVEXITSTAT[FIRST_ELEM])
		*(end - (data->singleq)) = '\0';
}

static char	*update_built(char *built, char *value, char curr_char, char *pos)
{
	char	*result;

	result = NULL;
	if (curr_char == 33 && *(pos - 1) == 33)
	{
		if (!built)
			result = exe_concat(NULL, value, NULL);
		else
			result = exe_concat(built, "'", built, value, "'", NULL);
	}
	else
	{
		if (!built)
			result = exe_concat(NULL, value, NULL);
		else
			result = exe_concat(built, built, value, NULL);
	}
	return (result);
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
	char	*suffix;
	char	*_built;

	temp = '\0';
	_built = NULL;
	suffix = NULL;
	while (iter && *iter)
	{
		if (!*(iter + 1) || *iter == DOLLAR || *iter == 33 || *iter == 34
			|| *iter == 92 || *iter == 47)
		{
			temp = *iter * (*(iter + 1) > 0);
			*iter = (*iter) * !(*(iter + 1) > 0);
			// suffix = get_suffix(iter);
			_built = process_iter(minivault, data, iter, _built);
			// _built = exe_concat(_built, _built, suffix, NULL);
			free(suffix);
			if (temp)
				*iter = temp;
			if (*iter == DOLLAR)
				data->pos = iter;
			else
				data->pos = NULL;
		}
		iter++;
	}
	if (!_built)
		_built = exe_concat(NULL, PLACEHOLDER, NULL);
	else if (_built && data->singleq)
		_built = exe_concat(_built, "'", _built, "'", NULL);
	return (_built);
}

void	process_string(char *curr, char **v_iter, t_minivault *minivault,
		t_strexp *data)
{
	char	*_magic;

	while (curr && *curr)
	{
		if (*curr == DOLLAR && data->expandable)
		{
			if (!*(curr + 1))
				break ;
			_put_end_break(curr + 1, data);
			_magic = alchemy(minivault, data, curr);
			if (!_magic)
				break ;
			*(curr - (data->quoted + data->singleq)) = '\0';
			_magic = exe_concat(_magic, *v_iter, _magic, NULL);
			free(*v_iter);
			*v_iter = _magic;
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
		_exp_validator(s_iter, &data);
		// printf("data->expandable: %d\n", data.expandable);
		// printf("data->quoted: %d\n", data.quoted);
		// printf("data->singleq: %d\n", data.singleq);
		if (_check_heredoc_deli(s_iter, vector))
			process_string(s_iter, v_iter, minivault, &data);
		v_iter++;
	}
}
