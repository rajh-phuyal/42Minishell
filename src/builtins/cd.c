/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:21 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/21 14:14:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clear_buff(char *buffer)
{
	int	i;

	i = 0;
	while (i < PATH_MAX)
		buffer[i++] = '\0';
	return (buffer);
}

static int	_display_err(t_builtin_err errnum, char *path)
{
	char	*err;

	err = NULL;
	if (errnum == NOHOME)
		err = exe_concat(NULL, "minibaiters: cd: ", "HOME not set", NULL);
	if (errnum == NOFILEORDIR)
		err = exe_concat(NULL, "minibaiters: cd: ", path,
				": No such file or directory", NULL);
	else if (errnum == NOPERM)
		err = exe_concat(NULL, "minibaiters: cd: ", "permission denied", NULL);
	else if (errnum == FILENOFOUND)
		err = exe_concat(NULL, "minibaiters: cd: ", "file not found", NULL);
	else if (errnum == MULTIARG)
		err = exe_concat(NULL, "minibaiters: cd: ", "too many arguments", NULL);
	if (err)
	{
		ft_putendl_fd(err, STDERR_FILENO);
		free(err);
	}
	return (FAILURE);
}

static int	_goto(t_minivault *minivault, char *path)
{
	char	*key;
	char	buffer[PATH_MAX];

	key = OLDPWD;
	if (!get_env(minivault, OLDPWD))
		key = ft_strdup(OLDPWD);
	if (getcwd(buffer, sizeof(buffer)))
		set_env(minivault, key, ft_strdup(buffer), (1 << 1));
	if (chdir(path) < 0)
		return (_display_err(NOFILEORDIR, path));
	clear_buff(buffer);
	if (getcwd(buffer, sizeof(buffer)))
	{
		set_env(minivault, "PWD", ft_strdup(buffer), (1 << 1));
		return (SUCCESS);
	}
	return (SUCCESS);
}

static int	_validate_path_types(t_minivault *minivault, char *path)
{
	struct stat	_file_stat;

	if (!stat(path, &_file_stat))
	{
		if (S_ISDIR(_file_stat.st_mode))
		{
			if (!access(path, X_OK))
				return (_goto(minivault, path));
			else
				return (_display_err(NOPERM, path));
		}
		else if (S_ISREG(_file_stat.st_mode))
			return (_goto(minivault, path));
		else
			return (_display_err(NOFILEORDIR, path));
	}
	else
		return (_display_err(NOFILEORDIR, path));
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
			return (_display_err(NOHOME, homepath));
	}
	else if (args && args->next)
		return (_display_err(MULTIARG, NULL));
	else if (args && args->word)
		return (_validate_path_types(minivault, args->word));
	return (SUCCESS);
}
