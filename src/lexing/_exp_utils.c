/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:01:34 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:01:36 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_concat(char *prev, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, prev);
	_built = concat_all(args);
	va_end(args);
	if (prev)
		free(prev);
	prev = NULL;
	return (_built);
}

bool	unpack_var(t_strexp *data, bool quoted, bool singleq, bool expandable)
{
	data->quoted = quoted;
	data->singleq = singleq;
	data->expandable = expandable;
	return (expandable);
}

bool	_is_heredoc_deli(char *str, char **vector)
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

void	_put_end_break(char *start, t_strexp *data)
{
	char	*end;

	end = start;
	while (end && *(end + 1))
		end++;
	if (data->quoted && *(start + 1) != PREVEXITSTAT[FIRST_ELEM])
	{
		if (*end == 34 || *end == 39)
			*(end - (data->singleq)) = '\0';
	}
}

char	*get_suffix(char *str)
{
	char	*suffix;
	char	*temp;

	temp = str;
	suffix = NULL;
	if (!str)
		return (NULL);
	while (temp && *temp && *temp != DOLLAR[0])
		temp++;
	if (temp && *temp == DOLLAR[0])
		suffix = ft_substr(str, 0, temp - str);
	else
		suffix = ft_substr(str, 0, ft_strlen(str) + 1);
	return (suffix);
}
