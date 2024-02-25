/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:20:14 by jalves-c          #+#    #+#             */
/*   Updated: 2023/06/14 16:05:35 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_matrix(char **matrix)
{
	size_t	y;
	size_t	size;

	y = 0;
	size = 0;
	if (!matrix)
		return ;
	while (matrix[size] != 0)
		size++;
	if (size == 0)
		return ;
	while (y < size)
		ft_printf("%s\n", matrix[y++]);
}
