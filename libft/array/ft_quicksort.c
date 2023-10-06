/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:30:17 by rphuyal           #+#    #+#             */
/*   Updated: 2023/05/22 16:42:13 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// quicksort with recursion
void    ft_quicksort(int *array, int left, int right)
{
    int pivot;
    int i;
    int j;
    int temp;

    if (left < right)
    {
        pivot = left;
        i = left;
        j = right;
        while (i < j)
        {
            while (array[i] <= array[pivot] && i < right)
                i++;
            while (array[j] > array[pivot])
                j--;
            if (i < j)
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        temp = array[pivot];
        array[pivot] = array[j];
        array[j] = temp;
        ft_quicksort(array, left, j - 1);
        ft_quicksort(array, j + 1, right);
    }
}