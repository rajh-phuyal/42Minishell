/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:55:46 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/17 14:46:46 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_session_envars(t_envs *envs, int outfd)
{
	while (envs)
	{
		if (envs->session && !envs->internal)
		{
			ft_putstr_fd(envs->key, outfd);
			ft_putstr_fd("=", outfd);
			ft_putstr_fd(envs->value, outfd);
			ft_putstr_fd("\n", outfd);
		}
		envs = envs->next;
	}
}

void    _env(t_minivault *minivault, char *key, char *value)
{
    int		outfd;

    outfd = 1; //? maybe minivauult->outfd
	if (key && !value)
	{
        error(minivault, CMDNOTFOUND, "env: : No such file or directory", key);
		return ;
	}
	print_session_envars(minivault->envs, outfd);
    if (key && value)
    {
        ft_putstr_fd(key, outfd);
        ft_putstr_fd("=", outfd);
        ft_putstr_fd(value, outfd);
        ft_putstr_fd("\n", outfd);
    }
	set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
}