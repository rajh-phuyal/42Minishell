/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:40:16 by jalves-c          #+#    #+#             */
/*   Updated: 2022/12/05 16:40:18 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chech_if_trimable(char const *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_put_in_arr(char *arr, const char *str, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
		arr[i++] = str[start++];
	arr[i] = '\0';
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*newstr;
	int		start;
	int		end;

	start = 0;
	if (!str || !set)
		return (NULL);
	while (str[start] && ft_chech_if_trimable(set, str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && ft_chech_if_trimable(set, str[end]))
		end--;
	newstr = malloc(sizeof(char) * (end - start + 2));
	if (!newstr)
		return (NULL);
	ft_put_in_arr(newstr, str, start, end);
	return (newstr);
}
