/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:35:41 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/13 22:45:10 by rajphuyal        ###   ########.fr       */
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
		add_env_node(minivault, splitted[0], splitted[1]);
		free(splitted);
	}
}

void	init_error(t_minivault *minivault)
{
	minivault->error = malloc(sizeof(t_error));
	minivault->error->status = 0;
	minivault->error->message = NULL;
	minivault->error->err_token = NULL;
}

int	init_minivault(t_minivault *minivault, char **envs)
{
	minivault->envs = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	minivault->builtin_list = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	minivault->env_list = envs;
	minivault->path = ft_split(getenv("PATH"), ':');
	init_envs(minivault, envs);
	init_error(minivault);
	return (0);
}
