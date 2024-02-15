#include "minishell.h"

static bool	f_ok_x(const char *exec_path)
{
	struct stat	statbuf;

	if (stat(exec_path, &statbuf) == 0 && S_ISREG(statbuf.st_mode))
	{
		if ((statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP) || \
			(statbuf.st_mode & S_IXOTH))
			return (true);
	}
	return (false);
}

static bool	is_valid_path(const char *exec_path)
{
	return (access(exec_path, F_OK) == 0 && \
			access(exec_path, X_OK) == 0 && \
			f_ok_x(exec_path));
}

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
		if (is_valid_path(temp))
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
	if (is_valid_path(exec_name))
		return (ft_strdup(exec_name));
	env_path = get_env(minivault, "PATH");
	if (!env_path)
		return (NULL);
	env_path_list = ft_split(env_path, ':');
	exec_path = get_full_path(env_path_list, exec_name);
	liberate_vector(env_path_list);
	return (exec_path);
}
