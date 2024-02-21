/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:56:08 by jalves-c          #+#    #+#             */
/*   Updated: 2023/03/06 15:01:46 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (dst == NULL && src == NULL)
		return (0);
	else if (dst > src)
		while (n-- > 0)
			((char *)dst)[n] = ((char *)src)[n];
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
