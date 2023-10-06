/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:54:05 by jalves-c          #+#    #+#             */
/*   Updated: 2022/12/05 16:54:06 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	strsize;

	strsize = ft_strlen(s);
	d = (char *)malloc(strsize + 1);
	if (!d)
		return (0);
	ft_memcpy(d, s, strsize);
	d[strsize] = 0;
	return (d);
}
