/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:55:46 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/25 21:34:38 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    _env(t_minivault *minivault)
{
	t_envs	*envs;

	envs = minivault->envs;
	while (envs)
	{
		if (envs->session && !envs->internal)
		{
			ft_putstr_fd(envs->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(envs->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		envs = envs->next;
	}
	set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
}