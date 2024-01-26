/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/26 11:52:37 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_declare_session_envar(t_envs *curr, int out_fd)
{
    ft_putstr_fd("declare -x ", out_fd);
    ft_putstr_fd(curr->key, out_fd);
    ft_putstr_fd("=\"", out_fd);
    ft_putstr_fd(curr->value, out_fd);
    ft_putstr_fd("\"\n", out_fd);
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

//? its not exporting shit, fix it!
void    _export(t_minivault *minivault, t_word *args, int out_fd)
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
                _declare_session_envar(curr, out_fd);
            iter++;
        }
        if (sorted)
            free(sorted);
    }
    set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
}
