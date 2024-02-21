/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:05 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 19:28:55 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_free_or_not(char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		if (i >= 2)
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
	int		tmp;
	char	**splitted;

	i = -1;
	while (envs[++i])
	{
		splitted = ft_split(envs[i], '=');
		if (ft_strlen(splitted[FIRST_ELEM]) == ft_strlen(SHELLEVEL) && \
			ft_strncmp(splitted[FIRST_ELEM], SHELLEVEL, \
			ft_strlen(SHELLEVEL)) == 0)
		{
			tmp = ft_atoi(splitted[SECOND_ELEM]);
			add_env_node(minivault, splitted[FIRST_ELEM], \
				ft_itoa(tmp + 1), (1 << 2));
			free(splitted[SECOND_ELEM]);
		}
		else
			add_env_node(minivault, splitted[FIRST_ELEM], \
				splitted[SECOND_ELEM], (1 << 2));
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
	init_envs(minivault, envs);
	init_cycle_vars(minivault);
	minivault->path = ft_split(get_env(minivault, "PATH"), ':');
	return (0);
}
