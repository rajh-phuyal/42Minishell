/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:35:41 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/11/02 14:49:40 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envs(t_minivault *minivault, char **envs)
{
	int		i;
	char	**splitted;

	i = -1;
	while (envs[++i])
	{
		splitted = ft_split(envs[i], '=');
		minivault->envs = add_env_node(minivault->envs, splitted[0], splitted[1]);
		free(splitted);
	}
}

int	init_minivault(t_minivault *minivault, char **envs)
{
	minivault->envs = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	init_envs(minivault, envs);
	return (0);
}
