/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:02 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:23:03 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_minivault *minivault, char *key, \
								char *value, int identifier)
{
	t_envs	*new;
	t_envs	*envs;

	new = (t_envs *)malloc(sizeof(t_envs));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->internal = (identifier >> 1) & 1;
	new->session = (identifier >> 2) & 1;
	new->next = NULL;
	if (!minivault->envs)
	{
		minivault->envs = new;
		return ;
	}
	envs = minivault->envs;
	while (envs->next)
		envs = envs->next;
	envs->next = new;
}

char	*get_env(t_minivault *minivault, char *key)
{
	t_envs	*envs;

	if (!key)
	{
		return (NULL);
	}
	envs = minivault->envs;
	while (envs)
	{
		if (ft_strlen(envs->key) == ft_strlen(key) && \
			ft_strncmp(envs->key, key, ft_strlen(key)) == 0)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

t_envs	*get_env_node(t_minivault *minivault, char *key)
{
	t_envs	*envs;

	if (!key)
	{
		return (NULL);
	}
	envs = minivault->envs;
	while (envs)
	{
		if (ft_strlen(envs->key) == ft_strlen(key) && \
			ft_strncmp(envs->key, key, ft_strlen(key)) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

void	set_env(t_minivault *minivault, char *key, char *value, int identifier)
{
	t_envs	*envs;

	envs = minivault->envs;
	while (envs)
	{
		if (ft_strlen(envs->key) == ft_strlen(key) && \
			ft_strncmp(envs->key, key, ft_strlen(key)) == 0)
		{
			free(envs->value);
			envs->value = value;
			return ;
		}
		envs = envs->next;
	}
	add_env_node(minivault, key, value, identifier);
}

void	unset_env(t_minivault *minivault, char *key)
{
	t_envs	*envs;
	t_envs	*temp;

	temp = NULL;
	envs = minivault->envs;
	while (envs)
	{
		if (ft_strlen(envs->key) == ft_strlen(key) && \
			ft_strncmp(envs->key, key, ft_strlen(key)) == 0)
		{
			free(envs->value);
			free(envs->key);
			if (temp)
				temp->next = envs->next;
			if (envs == minivault->envs)
				minivault->envs = envs->next;
			free(envs);
			break ;
		}
		temp = envs;
		envs = envs->next;
	}
}
