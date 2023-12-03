/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/03 01:50:52 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void    out_to_file(int file, char *str)
{
    if (!str)
		return ;
    write(file, str, ft_strlen(str));
}

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
            out_to_file(1, "declare -x ");
            out_to_file(1, *iter);
            out_to_file(1, "=\"");
            out_to_file(1, get_env(minivault, *iter));
            out_to_file(1, "\"\n");
            iter++;
        }
        if (sorted)
            free(sorted);
        return ;
    }
}

