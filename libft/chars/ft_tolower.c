/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:11:26 by rphuyal           #+#    #+#             */
/*   Updated: 2022/12/29 19:24:42 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* converts a given char to lowercase*/
int	ft_tolower(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return (ch + 32);
	else
		return (ch);
}
