/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:35:41 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/11/22 19:19:55 by jalves-c         ###   ########.fr       */
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

char	**get_path(char **env)
{
	int 	i = 0;
	char	*temp;
	char	**path;

	while(env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			temp = ft_strdup(env[i] + 5);
			path = ft_split(temp, ':');
			free(temp);
			return (path);
		}
		i++;
	}
	write(2, "PATH NOT FOUND\n", 15);
	exit(1); // TODO: error management
}

int	init_minivault(t_minivault *minivault, char **envs)
{
	minivault->envs = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	minivault->builtin_list = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	minivault->path = get_path(envs);
	init_envs(minivault, envs);
	return (0);
}
