/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:37:30 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/29 00:37:34 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_envlen(t_envs *envs)
{
	int	len;

	len = 0;
	while (envs->next)
	{
		len++;
		envs = envs->next;
	}
	return (len);
}

void	data_envs(t_envs *envs, char **data, int ACT)
{
	int	i;

	i = 0;
	while (envs->next)
	{
		if (ACT == GET)
			data[i] = envs->key;
		else if (ACT == PUT)
			envs->key = data[i];
		envs = envs->next;
		i++;
	}
}

int	partition(char **data, int start, int end)
{
	int		i;
	int		j;
	char	*pivot;
	char	*temp;

	pivot = data[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (ft_strncmp(data[j], pivot, ft_strlen(data[j])) < 0)
		{
			i++;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
		j++;
	}
	temp = data[i + 1];
	data[i + 1] = data[end];
	data[end] = temp;
	return (i + 1);
}

void	quicksort(char **data, int start, int end)
{
	int	pivot;

	if (start < end)
	{
		pivot = partition(data, start, end);
		quicksort(data, start, pivot - 1);
		quicksort(data, pivot + 1, end);
	}
}

void	envsort(t_envs *envs)
{
	int		len;
	char	**data;

	len = get_envlen(envs);
	data = (char **)malloc(sizeof(char *) * (len + 1));
	data[len] = NULL;
	data_envs(envs, data, GET);
	quicksort(data, 0, len - 1);
	data_envs(envs, data, PUT);
	free(data);
}
