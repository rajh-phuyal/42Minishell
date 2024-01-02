/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2024/01/01 19:10:18 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_declare_session_envar(t_envs *curr, int outfd)
{
    ft_putstr_fd("declare -x ", outfd);
    ft_putstr_fd(curr->key, outfd);
    ft_putstr_fd("=\"", outfd);
    ft_putstr_fd(curr->value, outfd);
    ft_putstr_fd("\"\n", outfd);
}

static void add_args_to_env(t_minivault *minivault, t_word *args)
{
    char    **iter;

    while (args)
    {
        iter = ft_split(args->word, '=');
        if (!iter)
            break ;
        if (iter[FIRST_ELEM] && iter[SECOND_ELEM])
            add_env_node(minivault, iter[FIRST_ELEM], iter[SECOND_ELEM], (1 << 2));
        else if (iter[FIRST_ELEM])
            add_env_node(minivault, iter[FIRST_ELEM], "", (1 << 2));
        if (iter)
            free (iter);
        args = args->next;
    }
}

void    _export(t_minivault *minivault, t_word *args)
{
    t_envs  *curr;
    char    **iter;
    char    **sorted;

    if (args)
        add_args_to_env(minivault, args);
    else
    {
        sorted = envsort(minivault->envs);
        iter = sorted;
        while (iter && *iter)
        {
            curr = get_env_node(minivault, *iter);
            if (curr && (curr->session) && !(curr->internal))
                _declare_session_envar(curr, STDOUT_FILENO);
            iter++;
        }
        if (sorted)
            free(sorted);
    }
    set_env(minivault, PREVEXITSTAT, ft_itoa(SUCCESS), (1 << 1));
}
