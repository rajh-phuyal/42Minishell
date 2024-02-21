/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:04:52 by jalves-c          #+#    #+#             */
/*   Updated: 2023/05/18 12:23:01 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_multiple(unsigned int count, ...)
{
	va_list	args;
	void	*arg;

	va_start(args, count);
	while (count)
	{
		arg = va_arg(args, void *);
		free(arg);
		count--;
	}
	va_end(args);
}
