/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:55:58 by rajphuyal         #+#    #+#             */
/*   Updated: 2024/01/28 19:47:00 by rphuyal          ###   ########.fr       */
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

static	int	_display_err(t_builtin_err errnum)
{
	char	*err;
	
	err = NULL;
	if (errnum == NOHOME)
		err = exe_concat(NULL, "minivault: cd: ", "HOME not set", NULL);
	else if (errnum == NOPERM)
		err = exe_concat(NULL, "minivault: cd: ", "permission denied", NULL);
	else if (errnum == FILENOFOUND)
		err = exe_concat(NULL, "minivault: ", "file not found", NULL);
	if (err)
	{
		printf("%s\n", err);
		free(err);
	}
	return (FAILURE);
}

static	int	_goto(t_minivault *minivault, char *path)
{
	char    buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		set_env(minivault, "OLDPWD", ft_strdup(buffer), (1 << 1));
	if (chdir(path) < 0)
		return (_display_err(NOPERM));
	clear_buff(buffer);
	if (getcwd(buffer, sizeof(buffer)))
	{
		set_env(minivault, "PWD", ft_strdup(buffer), (1 << 1));
		return (SUCCESS);
	}
	return (SUCCESS);
}

static	int	_validate_path_types(t_minivault *minivault, char *path)
{
	struct stat	_file_stat;

	if (!stat(path, &_file_stat))
	{
		if (S_ISDIR(_file_stat.st_mode))
		{
			if (!access(path, X_OK))
				return (_goto(minivault, path));
			else
				return (_display_err(NOPERM));
		}
		else if (S_ISREG(_file_stat.st_mode))
			return (_goto(minivault, path));
		else
			return (_display_err(FILENOFOUND));
	}
	else
		return (_display_err(FILENOFOUND));
}

int	_cd(t_minivault *minivault, t_word *args)
{
	char	*homepath;

	if (!args)
	{
		homepath = get_env(minivault, "HOME");
		if (homepath)
			return (_goto(minivault, homepath));
		else
			return (_display_err(NOHOME));
	}
	else if (args && args->word)
		return (_validate_path_types(minivault, args->word));
	return (SUCCESS);
}
