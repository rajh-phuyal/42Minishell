/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:05:13 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:05:14 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_path(char **path_list, char *command)
{
	char	*temp;
	char	*freeable;
	int		i;

	i = 0;
	while (path_list && path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		freeable = temp;
		temp = ft_strjoin(temp, command);
		free(freeable);
		if (owner_can_execute(temp))
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

char	*get_exec_path(t_minivault *minivault, char *exec_name)
{
	char	*env_path;
	char	**env_path_list;
	char	*exec_path;

	exec_path = NULL;
	if (!exec_name)
		return (NULL);
	if (owner_can_execute(exec_name))
		return (ft_strdup(exec_name));
	env_path = get_env(minivault, "PATH");
	if (!env_path)
		return (NULL);
	env_path_list = ft_split(env_path, ':');
	exec_path = get_full_path(env_path_list, exec_name);
	liberate_vector(env_path_list);
	if (!exec_path)
		return (ft_strdup(exec_name));
	return (exec_path);
}
