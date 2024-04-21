/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:50:34 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 21:50:39 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_unset(t_minivault *minivault, t_word *args)
{
	t_envs	*curr;

	while (args)
	{
		curr = get_env_node(minivault, args->word);
		if (curr && curr->session)
			unset_env(minivault, args->word);
		args = args->next;
	}
	set_env(minivault, PREVEXITSTAT, ft_itoa(SUCCESS), (1 << 1));
}
