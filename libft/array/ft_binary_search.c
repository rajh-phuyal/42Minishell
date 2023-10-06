/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:29:59 by rphuyal           #+#    #+#             */
/*   Updated: 2023/05/22 16:41:54 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// binary search with recursion
int ft_binary_search(int *array, int left, int right, int find)
{
    int middle;

    if (right >= left)
    {
        middle = (left + right) / 2;
        if (array[middle] == find)
            return (middle);
        else if (array[middle] > find)
            return (ft_binary_search(array, left, middle - 1, find));
        else
            return (ft_binary_search(array, middle + 1, right, find));
    }
    return (-1);
}