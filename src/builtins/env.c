/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:49:51 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 21:49:52 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_minivault *minivault, int out_fd)
{
	t_envs	*envs;

	envs = minivault->envs;
	while (envs)
	{
		if (envs->session && !envs->internal)
		{
			if (envs->key && envs->value)
			{
				ft_putstr_fd(envs->key, out_fd);
				ft_putstr_fd("=", out_fd);
				ft_putstr_fd(envs->value, out_fd);
				ft_putstr_fd("\n", out_fd);
			}
		}
		envs = envs->next;
	}
	set_env(minivault, PREVEXITSTAT, ft_itoa(SUCCESS), (1 << 1));
}
