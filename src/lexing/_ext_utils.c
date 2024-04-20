/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ext_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:24:39 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/20 15:19:22 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (*str == DOLLAR[0])
			return (true);
		str++;
	}
	return (false);
}

void	finilize_magic_str(char **v_iter, char *curr, char *_magic,
		t_strexp *data)
{
	char	*temp;

	temp = *v_iter;
	while (temp && *temp && *temp != DOLLAR[0])
		temp++;
	if (*temp)
		*temp = '\0';
	if (data->singleq && !data->expandable)
	{
		*temp = DOLLAR[0];
		free(_magic);
		return ;
	}
	else if (!data->singleq && data->expandable)
		_magic = exe_concat(_magic, *v_iter, _magic, curr, NULL);
	else if (!data->expandable)
	{
		*temp = DOLLAR[0];
		_magic = exe_concat(_magic, *v_iter, _magic, NULL);
	}
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

char	*build_or_not_build(char *_built, t_strexp *data)
{
	if (!_built)
		return (exe_concat(NULL, PLACEHOLDER, NULL));
	else if (_built && data->singleq)
	{
		return (exe_concat(_built, DOUBLEQUOTES, "'", \
			_built, "'", DOUBLEQUOTES, NULL));
	}
	return (_built);
}
