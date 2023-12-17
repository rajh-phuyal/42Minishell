/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/17 14:37:19 by rajphuyal        ###   ########.fr       */
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

void    _export(t_minivault *minivault, char *key, char *value)
{
    t_envs  *curr;
    char    **iter;
    char    **sorted;

    if (key && value) // TODO: here you could have multiple key value pairs, if so loop through and set
        set_env(minivault, key, value, (1 << 2));
    else
    {
        sorted = envsort(minivault->envs);
        iter = sorted;
        while (iter && *iter)
        {
            curr = get_env_node(minivault, *iter);
            if (curr && (curr->session) && !(curr->internal))
                _declare_session_envar(curr, 1);
            iter++;
        }
        if (sorted)
            free(sorted);
    }
    set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
}
