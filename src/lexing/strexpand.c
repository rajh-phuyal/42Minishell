/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strexpand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:18 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:18:20 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cleaner(t_strexp *data)
{
	data->quoted = false;
	data->singleq = false;
	data->isHereDoc = false;
	data->expandable = false;
	data->_pos = NULL;
}

static void	_exp_validator(char *str, t_strexp *data)
{
	char		*end;

	end = str;
	while (end && *(end + 1))
		end++;
	while (str && *str && *str != DOLLAR && *str != '\'' && *str != '"')
		str++;
	if (*str == DOLLAR)
		data->expandable = true;
	if (*str == *end && *end == '\'')
	{
		data->quoted = true;
		data->singleq = true;
		data->expandable = false;
		return ;
	}
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
	data->expandable = true;
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

char	*exe_concat(char *prev, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, prev);
	_built = concat_all(args);
	va_end(args);
	if (prev)
		free(prev);
	return (_built);
}

bool	_check_heredoc_deli(char *str, char **vector)
{
	if (vector && *vector == str)
		return (true);
	while (vector && *vector)
	{
		if (!ft_strncmp(*vector, "<<", ft_strlen(*vector)))
		{
			if (vector && *(vector + 1) == str)
				return (false);
		}
		vector++;
	}
	return (true);
}

char	*get_suffix(char *pos)
{
	char	temp;
	char	*start;
	char	*suffix;

	suffix = NULL;
	start = pos;
	temp = '\0';
	while (pos && *pos)
	{
		if (!*(pos + 1) || *pos == DOLLAR || *pos == '\'' || *pos == '"')
		{
			if (*(pos + 1))
			{
				temp = *pos;
				*pos = '\0';
			}
			suffix = exe_concat(NULL, start, NULL);
			if (temp)
				*pos = temp;
			break ;
		}
		pos++;
	}
	return (suffix);
}

static char	*alchemy(t_minivault *minivault, t_strexp *data, char *start)
{
	char	temp;
	char	*_pos;
	char	*value;
	char	*_built;
	char	*suffix;

	_pos = start;
	start++;
	temp = '\0';
	_built = NULL;
	suffix = NULL;
	_put_end_break(start, data);
	while (start && *start)
	{
		if (!*(start + 1) || *start == DOLLAR \
		|| *start == '\'' || *start == '"')
		{
			if (*(start + 1))
			{
				temp = *start;
				*start = '\0';
			}
			if (_pos && *(_pos + 1) == PREVEXITSTAT[FIRST_ELEM])
			{
				suffix = get_suffix(_pos + 2);
				value = get_env(minivault, PREVEXITSTAT);
			}
			else if (_pos)
				value = get_env(minivault, _pos + 1);
			if (value)
			{
				if (*(start) == '\'' && *(_pos - 1) == '\'')
				{
					if (!_built)
						_built = exe_concat(_built, value, suffix, NULL);
					else
					{
						_built = exe_concat(_built, "'", \
						_built, "'", value, suffix, NULL);
					}
				}
				if (!_built)
					_built = exe_concat(_built, "", value, suffix, NULL);
				else
					_built = exe_concat(_built, _built, value, suffix, NULL);
				if (suffix)
				{
					free(suffix);
					suffix = NULL;
				}
			}
			if (temp)
			{
				*start = temp;
				temp = '\0';
			}
			if (*start == DOLLAR)
				_pos = start;
			else
				_pos = NULL;
		}
		start++;
	}
	if (!_built)
		_built = exe_concat(NULL, PLACEHOLDER, NULL);
	else if (data->singleq)
		_built = exe_concat(_built, "'", _built, "'", NULL);
	return (_built);
}

void	strexpand(t_minivault *minivault, char **vector)
{
	t_strexp	data;
	char		*s_iter;
	char		*_magic;
	char		**v_iter;

	v_iter = vector;
	while (v_iter && *v_iter)
	{
		s_iter = *v_iter;
		_cleaner(&data);
		_exp_validator(s_iter, &data);
		if (_check_heredoc_deli(s_iter, vector))
		{
			while (s_iter && *s_iter)
			{
				if (*s_iter == DOLLAR && data.expandable)
				{
					if (!*(s_iter + 1))
						break ;
					_magic = alchemy(minivault, &data, s_iter);
					if (!_magic)
						break ;
					*(s_iter - (data.quoted + data.singleq)) = '\0';
					_magic = exe_concat(_magic, *v_iter, _magic, NULL);
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
