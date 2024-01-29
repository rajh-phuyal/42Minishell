/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:32 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:18:33 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_concat(char *prev, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, dummy);
	_built = concat_all(args);
	va_end(args);
	if (prev)
		free(prev);
	return (_built);
}
