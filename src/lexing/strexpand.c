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
	while (end && *(end + 1) && *end != DOLLAR && *end != 33 && *end != 34)
		end++;
	while (str && *str && *str != DOLLAR && *str != 33 && *str != 34)
		str++;
	if (*str == DOLLAR)
		return (unpack_var(data, false, false, true));
	if (*str == *end && *end == 33)
		return (unpack_var(data, true, true, false));
	else if (*str == *end && *end == 34 && *(str + 1) == 33)
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

static char	*update_built(char *built, char *value, char *suffix,
		char current_char, char *pos)
{
	char	*result;

	result = NULL;
	if (current_char == 33 && *(pos - 1) == 33)
	{
		if (!built)
			result = exe_concat(NULL, value, suffix, NULL);
		else
			result = exe_concat(built, "'", built, value, "'", suffix, NULL);
	}
	else
	{
		if (!built)
			result = exe_concat(NULL, value, suffix, NULL);
		else
			result = exe_concat(built, built, value, suffix, NULL);
	}
	free(suffix);
	return (result);
}

static char	*process_iter(t_minivault *minivault, t_strexp *data, char *iter,
		char *built)
{
	char	*value;
	char	*suffix;

	value = NULL;
	suffix = NULL;
	if (data->pos && *(data->pos + 1) == PREVEXITSTAT[FIRST_ELEM])
	{
		suffix = get_suffix(iter + 2);
		value = get_env(minivault, PREVEXITSTAT);
	}
	else if (data->pos)
	{
		if (*(iter + 1))
			suffix = get_suffix(iter);
		value = get_env(minivault, data->pos + 1);
	}
	if (value)
		built = update_built(built, value, suffix, *iter, data->pos);
	return (built);
}

static char	*finalize_built(char *built, t_strexp *data)
{
	char	*_final;

	_final = NULL;
	if (built && data->singleq)
	{
		_final = exe_concat(NULL, "'", built, "'", NULL);
		return (_final);
	}
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
		if (!*(iter + 1) || *iter == DOLLAR || *iter == 33 || *iter == 34
			|| *iter == 92 || *iter == 47)
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
	if (!_built)
		_built = exe_concat(NULL, PLACEHOLDER, NULL);
	_built = finalize_built(_built, data);
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
		if (_check_heredoc_deli(s_iter, vector))
			process_string(s_iter, v_iter, minivault, &data);
		v_iter++;
	}
}
