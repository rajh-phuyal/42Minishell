#include "minishell.h"

void	_cleaner(t_strexp *data)
{
	data->quoted = false;
	data->singleq = false;
	data->expandable = false;
	data->pos = NULL;
}

bool	_has_expander(char *str)
{
	if (!str)
		return (false);
	while (str && *str)
	{
		if (*str == DOLLAR)
			return (true);
		str++;
	}
	return (false);
}

void	finilize_magic_str(char **v_iter, char *curr, char *_magic,
		t_strexp *data)
{
	if (!data->expandable && data->quoted)
	{
		*(curr - (data->quoted + data->singleq)) = '\0';
		_magic = exe_concat(_magic, *v_iter, "'", DOUBLEQUOTES,
			curr, DOUBLEQUOTES, "'", NULL);
	}
	else
		_magic = exe_concat(_magic, *v_iter, _magic, NULL);
	free(*v_iter);
	*v_iter = _magic;
}

char	*update_built(char *built, char *value, char curr_char, char *pos)
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

char *build_or_not_build(char *_built, t_strexp *data)
{
	if (!_built)
		return (exe_concat(NULL, PLACEHOLDER, NULL));
	else if (_built && data->singleq)
	{
		return (exe_concat(_built, DOUBLEQUOTES, "'", _built,
			"'", DOUBLEQUOTES, NULL));
	}
	return (_built);
}

