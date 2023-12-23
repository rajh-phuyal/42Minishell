/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:55:58 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/23 16:03:48 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*clear_buff(char *buffer)
{
	int		i;

	i = 0;
	while (i < PATH_MAX)
		buffer[i++] = '\0';
	return (buffer);
}

static	void	_goto(t_minivault *minivault, char *path)
{
	char    buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		set_env(minivault, "OLDPWD", ft_strdup(buffer), (1 << 1));
	if (chdir(path) < 0)
		error(minivault, FAILURE, "minibaiters: cd: permission denied", "");
	clear_buff(buffer);
	if (getcwd(buffer, sizeof(buffer)))
	{
		set_env(minivault, "PWD", ft_strdup(buffer), (1 << 1));
		set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
	}
}

static	void	_validate_path_types(t_minivault *minivault,  char *path)
{
	struct stat	_file_stat;

	if (!stat(path, &_file_stat))
	{
		if (S_ISDIR(_file_stat.st_mode))
		{
			if (!access(path, X_OK))
				_goto(minivault, path);
			else
				error(minivault, FAILURE, "minibaiters: cd: permission denied", "");
		}
		else if (S_ISREG(_file_stat.st_mode))
			_goto(minivault, path);
		else
			error(minivault, FAILURE, "minibaiters: file not found", "");
		return ;
	}
	else
		error(minivault, FAILURE, "minibaiters: file not found", "");
}

/*
cd can take multiple paths, but will only consider the first path value
change later for: void    _cd(t_minivault *minivault, char **paths) and else if (path && *path)
*/
void    _cd(t_minivault *minivault, char *path)
{
	char	*homepath;

	//? if home not exist, cd no path won't work
	//? if cd -, don't treat it
	//? execute the chdir right away
	if (!path)
	{
		homepath = get_env(minivault, "HOME");
		if (homepath)
			_goto(minivault, homepath);
		else
			error(minivault, FAILURE, "minibaiters: cd: HOME not set", "");
	}
	else
		_validate_path_types(minivault, path);
}
