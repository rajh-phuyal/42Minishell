/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:05 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/21 18:37:07 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_free_or_not(char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		if (i >= 1)
			free(vec[i]);
		i++;
	}
	free(vec);
}

/*
to set only the internal to true -> (1 << 1)
to set only the session to true -> (1 << 2)
to set both to true -> (1 << 1) | (1 << 2)
to set both to false -> 0
*/
static void	init_envs(t_minivault *minivault, char **envs)
{
	int		i;
	char	*value;
	char	**splitted;

	i = -1;
	value = NULL;
	while (envs[++i])
	{
		splitted = ft_split(envs[i], '=');
		if (splitted && splitted[FIRST_ELEM])
			value = ft_strdup(getenv(splitted[FIRST_ELEM]));
		else
			continue ;
		if (!value)
			continue ;
		add_env_node(minivault, splitted[FIRST_ELEM], \
			value, (1 << 2));
		_free_or_not(splitted);
	}
	add_env_node(minivault, ft_strdup(PREVEXITSTAT), ft_strdup("0"), (1 << 1));
}

static void	init_cycle_vars(t_minivault *minivault)
{
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
}

int	init_minivault(t_minivault *minivault, char **envs)
{
	minivault->cmd_count = 0;
	minivault->cycles = 1;
	minivault->envs = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	minivault->env_list = envs;
	minivault->envs = NULL;
	init_fds(minivault);
	init_envs(minivault, envs);
	init_cycle_vars(minivault);
	minivault->path = NULL;
	if (get_env(minivault, "PATH"))
		minivault->path = ft_split(get_env(minivault, "PATH"), ':');
	return (0);
}
