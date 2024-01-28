/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:35:41 by rajphuyal         #+#    #+#             */
/*   Updated: 2024/01/01 18:08:35 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
to set only the internal to true -> (1 << 1)
to set only the session to true -> (1 << 2)
to set both to true -> (1 << 1) | (1 << 2)
to set both to false -> 0
*/
void	init_envs(t_minivault *minivault, char **envs)
{
	int		i;
	char	**splitted;

	i = -1;
	while (envs[++i])
	{
		splitted = ft_split(envs[i], '=');
		add_env_node(minivault, splitted[0], splitted[1], (1 << 2));
		free(splitted);
	}
	add_env_node(minivault, ft_strdup(PREVEXITSTAT), ft_strdup("0"), (1 << 1));
}

void	init_cycle_vars(t_minivault *minivault)
{
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
}

int	init_minivault(t_minivault *minivault, char **envs)
{
	minivault->cycles = 1;
	minivault->envs = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	minivault->env_list = envs;
	init_envs(minivault, envs);
	init_cycle_vars(minivault);
	minivault->path = ft_split(get_env(minivault, "PATH"), ':');
	return (0);
}
