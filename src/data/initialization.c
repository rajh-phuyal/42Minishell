/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:35:41 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/29 00:30:37 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_envs *envs)
{
	while (envs->next)
	{
		printf("[ (key): %s | (value): %s ]\n", envs->key, envs->value);
		envs = envs->next;
	}
}

void	init_envs(t_minivault *minivault, char **envs)
{
	int		i;
	char	**splitted;

	i = -1;
	while (envs[++i])
	{
		splitted = ft_split(envs[i], '='); // asume it only sends two strings, key and value
		minivault->envs = add_env_node(minivault->envs, splitted[0], splitted[1]);
		free(splitted);
	}
	envsort(minivault->envs);
	print_env_list(minivault->envs);
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
