/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:05:44 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:05:46 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	owner_can_execute(const char *file_path)
{
	struct stat	statbuf;

	return (access(file_path, F_OK) == 0 && \
			access(file_path, X_OK) == 0 && \
			stat(file_path, &statbuf) == 0 && \
			S_ISREG(statbuf.st_mode) && \
			(statbuf.st_mode & S_IXUSR));
}

int	get_status_owner_can_execute(const char *file_path)
{
	struct stat	statbuf;

	if (!file_path)
		return (127);
	if (stat(file_path, &statbuf))
		return (127);
	if (*file_path == '/' && S_ISDIR(statbuf.st_mode))
		return (126);
	if (*file_path == '.' && \
		access(file_path, F_OK) == 0 && \
		(access(file_path, X_OK) || \
		!S_ISREG(statbuf.st_mode)))
		return (126);
	return (127);
}

bool	owner_can_write(const char *file_path)
{
	struct stat	statbuf;

	return (access(file_path, F_OK) == 0 && \
			access(file_path, W_OK) == 0 && \
			stat(file_path, &statbuf) == 0 && \
			S_ISREG(statbuf.st_mode) && \
			(statbuf.st_mode & S_IWUSR));
}

bool	owner_can_read(const char *file_path)
{
	struct stat	statbuf;

	return (access(file_path, F_OK) == 0 && \
			access(file_path, R_OK) == 0 && \
			stat(file_path, &statbuf) == 0 && \
			S_ISREG(statbuf.st_mode) && \
			(statbuf.st_mode & S_IRUSR));
}
