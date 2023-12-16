/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/16 21:12:52 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_declare_session_envs(t_envs *curr, int outfd)
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

    if (key && value)
        set_env(minivault, key, value, (1 << 2));
    else
    {
        sorted = envsort(minivault->envs);
        iter = sorted;
        while (iter && *iter)
        {
            curr = get_env_node(minivault, *iter);
            if (curr && (curr->session) && !(curr->internal))
                _declare_session_envs(curr, 1);
            iter++;
        }
        if (sorted)
            free(sorted);
        return ;
    }
}
