/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/02 16:46:19 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sort_and_print()
{
    return ;
}

void    export(t_minivault *minivault, char *key, char *value)
{
    char    **sorted;

    // if passes the parameter add it to the env list
    // if not, print the sorted env list with declare -x prefix
    if (key && value)
        set_env(minivault, key, value);
    else
    {
        sorted = envsort(minivault->envs);
    }
}

// cmd (single)
// cmd (first) | cmd (last)
// cmd (first) | cmd (middle) | cmd (middle) | cmd (last)

// size of the pipeline
// its own place in the list
//
