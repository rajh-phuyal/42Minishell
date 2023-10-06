/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:53:55 by jalves-c          #+#    #+#             */
/*   Updated: 2022/12/05 16:53:56 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!str1 || !str2)
		return (NULL);
	newstr = malloc(sizeof(char) * ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!newstr)
		return (NULL);
	while (*str1)
		newstr[i++] = *str1++;
	while (*str2)
		newstr[i++] = *str2++;
	newstr[i] = '\0';
	return (newstr);
}
