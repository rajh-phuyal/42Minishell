/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/13 21:53:28 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    _export(t_minivault *minivault, char *key, char *value)
{
    char    **iter;
    char    **sorted;

    if (key && value)
        set_env(minivault, key, value);
    else
    {
        sorted = envsort(minivault->envs); // ? returns a sorted array of keys
        iter = sorted;
        while (iter && *iter)
        {
             // TODO: point to the right fd to send the output to
             // TODO: something like this: out_to_file(minivauult->outfd, str);
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(*iter, 1);
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(get_env(minivault, *iter), 1);
            ft_putstr_fd("\"\n", 1);
            iter++;
        }
        if (sorted)
            free(sorted);
        return ;
    }
}

