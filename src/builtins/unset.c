/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/25 20:17:40 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    _unset(t_minivault *minivault, t_word *args)
{
    t_envs	*curr;

	while (args)
	{
		curr = get_env_node(minivault, args->word);
		if (curr && curr->session)
			unset_env(minivault, args->word);
		args = args->next;
	}
	set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
}
