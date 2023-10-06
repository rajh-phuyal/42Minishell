/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:33:24 by rphuyal           #+#    #+#             */
/*   Updated: 2023/05/22 16:35:05 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// free_multiple(number of args to free, arg1, arg2, ..., argn)
void    free_multiple(unsigned int count, ...)
{
    va_list args;
    void    *arg;

    va_start(args, count);
    while (count)
    {
        arg = va_arg(args, void *);
        if (arg)
            free(arg);
        count--;
    }
    va_end(args);
}