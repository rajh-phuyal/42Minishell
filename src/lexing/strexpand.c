#include "minishell.h"

static	void	_cleaner(t_strexp *data)
{
	data->quoted = false;
	data->singleq = false;
	data->expandable = false;
	data->pos = NULL;
}

static bool	_exp_validator(char *str, t_strexp *data)
{
	char		*end;

	end = str;
	while (end && *(end + 1))
		end++;
	while (str && *str && *str != DOLLAR && *str != '\'' && *str != '"')
		str++;
	if (*str == DOLLAR)
		return (unpack_var(data, false, false, true));
	if (*str == *end && *end == '\'')
		return (unpack_var(data, true, true, false));
	else if (*str == *end && *end == '"' && *(str + 1) == '\'')
		return (unpack_var(data, true, true, true));
	else if (*str == *end && *end == '"')
		return (unpack_var(data, true, false, true));
	return (unpack_var(data, false, false, false));
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












static char *update_built(char *built, char *value, char *suffix, char current_char, char *pos)
{
    char	*result;

	result = NULL;
    if (current_char == '\'' && *(pos - 1) == '\'') {
        if (!built)
            result = exe_concat(NULL, value, suffix, NULL);
		else
            result = exe_concat(built, "'", value, "'", suffix, NULL);
    }
	else
	{
        if (!built)
            result = exe_concat(NULL, value, suffix, NULL);
		else
            result = exe_concat(built, value, suffix, NULL);
    }

    // Free the old built string if it's no longer needed
    if (built != NULL && built != result) {
        free(built);
    }

    return result;
}

static char *process_iter(t_minivault *minivault, t_strexp *data, char *iter, char *built)
{
    char temp = '\0';
    char *value = NULL;
    char *suffix = NULL;

    if (!*(iter + 1) || *iter == DOLLAR || *iter == '\'' || *iter == '"') {
        temp = *iter * (*(iter + 1) > 0);
        *iter = (*iter) * !(*(iter + 1) > 0);
        if (data->pos && *(data->pos + 1) == PREVEXITSTAT[FIRST_ELEM])
		{
            suffix = get_suffix(data->pos + 2);
            value = get_env(minivault, PREVEXITSTAT);
        }
		else if (data->pos)
            value = get_env(minivault, data->pos + 1);

        if (value)
            built = update_built(built, value, suffix, *iter, data->pos);
        if (temp)
            *iter = temp;
		if (*iter == DOLLAR)
			data->pos = iter;
		else if (*iter == '\'' && data->pos)
			data->pos = NULL;
    }
    return built;
}

static char *finalize_built(char *built, t_strexp *data)
{
	char *finalized;

	finalized = NULL;
    if (data->singleq) {
        finalized = exe_concat(NULL, "'", built, "'", NULL);
        if (built != finalized)
            free(built);
        return (finalized);
    }
    return (built);
}

// Simplified for demonstration. Implement missing logic as separate functions.
static char *alchemy(t_minivault *minivault, t_strexp *data, char *iter)
{
    char *_built;

	_built = NULL;
    while (iter && *iter)
	{
        _built = process_iter(minivault, data, iter, _built);
        iter++;
    }
    if (!_built)
        _built = exe_concat(NULL, PLACEHOLDER, NULL);
    else if (_built && data->singleq)
        _built = finalize_built(_built, data);
    return _built;
}


// Example helper function to process each string
void process_string(char **s_iter, char **v_iter, t_minivault *minivault, t_strexp *data)
{
	char	*_magic;

	while (*s_iter && **s_iter) {
		if (**s_iter == DOLLAR && data->expandable)
		{
			if (!*(*s_iter + 1))
				break;
			_put_end_break(*s_iter + 1, data);
			_magic = alchemy(minivault, data, *s_iter);
			if (!_magic)
				break;
			*(*s_iter - (data->quoted + data->singleq)) = '\0';
			_magic = exe_concat(_magic, *v_iter, _magic, NULL);
			free(*v_iter);
			*v_iter = _magic;
			break;
		}
		(*s_iter)++;
	}
}

void strexpand(t_minivault *minivault, char **vector)
{
    char	**v_iter;

	v_iter = vector;
    while (v_iter && *v_iter) {
        char *s_iter = *v_iter;
        t_strexp data;
        _cleaner(&data);
        _exp_validator(s_iter, &data);

        if (_check_heredoc_deli(s_iter, vector)) {
            process_string(&s_iter, v_iter, minivault, &data);
        }
        v_iter++;
    }
}
