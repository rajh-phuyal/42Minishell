/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/23 22:44:02 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    _unset(t_minivault *minivault, char **keys)
{
    // unset all the keys variable from the minivault->env if its a session variable
    // if the given key is not found in the minivault->env, no error is printed

    t_envs	*curr;

	while (keys && *keys)
	{
		curr = get_env_node(minivault, *keys);
		if (curr && curr->session)
			unset_env(minivault, *keys);
		keys++;
	}
	set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
}
