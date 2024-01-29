/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:48 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:18:50 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_all(va_list args)
{
	char	*iter;
	char	*temp;
	char	*_string;

	temp = NULL;
	_string = va_arg(args, char *);
	if (!_string)
	{
		return (temp);
	}
	_string = ft_strdup(_string);
	iter = va_arg(args, char *);
	while (iter)
	{
		temp = ft_strjoin(_string, iter);
		free(_string);
		_string = temp;
		if (!_string)
			return (NULL);
		iter = va_arg(args, char *);
	}
	return (_string);
}
