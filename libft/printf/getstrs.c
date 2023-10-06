/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:49:57 by rphuyal           #+#    #+#             */
/*   Updated: 2023/04/23 23:49:59 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	get_hex_len(unsigned long long n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_gethexstr(unsigned long long num, char *base)
{
	char	*str;
	int		i;
	int		base_len;

	i = get_hex_len(num);
	base_len = 0;
	while (base[base_len])
		base_len++;
	str = malloc(sizeof(char) * i + 1);
	str[i--] = '\0';
	while (num > 0 && i >= 0)
	{
		str[i--] = base[num % base_len];
		num /= base_len;
	}
	return (str);
}

int	get_int_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_getintstr(long n)
{
	char	*arr;
	int		len;
	long	i;

	len = get_int_len(n);
	i = n;
	arr = (char *)malloc(sizeof(char) * len + 1);
	if (!arr)
		return (NULL);
	*(arr + len) = '\0';
	if (i == 0)
		arr[0] = '0';
	else if (i < 0)
	{
		arr[0] = '-';
		i *= -1;
	}
	while (i)
	{
		arr[len - 1] = i % 10 + 48;
		len--;
		i = i / 10;
	}
	return (arr);
}
