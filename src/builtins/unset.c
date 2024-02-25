/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:47 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:22:48 by jalves-c         ###   ########.fr       */
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
