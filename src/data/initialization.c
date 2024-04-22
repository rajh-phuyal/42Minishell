/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:52:26 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/22 10:36:16 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_free_or_not(char **vec, int start)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		if (i >= start)
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
		if (!value && !splitted)
			continue ;
		else if (!value && splitted)
		{
			_free_or_not(splitted, 0);
			continue ;
		}
		add_env_node(minivault, splitted[FIRST_ELEM], \
			value, (1 << 2));
		_free_or_not(splitted, 1);
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
	minivault->cmd_count = 1;
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
