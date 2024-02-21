/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:13 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 00:00:30 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_fd_great(t_minivault *minivault, t_command *command, const char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK) != 0)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (owner_can_write(file))
		fd = open(file, O_WRONLY | O_TRUNC);
	else
	{
		error(minivault, REDIRFAIL, true, file, \
			": ", "Permission denied", NULL);
			command->status = 1;
	}
	return (fd);
}

static int	assign_fd_dgreat(t_minivault *minivault, t_command *command, const char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK) != 0)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
	else if (owner_can_write(file))
		fd = open(file, O_WRONLY | O_APPEND);
	else
	{	
		command->status = 1;
		error(minivault, REDIRFAIL, true, file, \
		": ", "Permission denied", NULL);
	}
	return (fd);
}

static int	assign_fd_less(t_minivault *minivault, t_command *command, const char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK) != 0)
	{
		error(minivault, REDIRFAIL, true, file, ": ", \
		"No such file or directory", NULL);
		command->status = 1;
		return (fd);
	}
	if (owner_can_read(file))
		fd = open(file, O_RDONLY);
	else
	{
		error(minivault, REDIRFAIL, true, file, \
		": ", "Permission denied", NULL);
		command->status = 1;
	}
	return (fd);
}

int	assign_fd(t_minivault *minivault, t_command *command, \
			t_operation operator, const char *file)
{
	int	fd;

	fd = -1;
	if (command->status)
		return (-1);
	if (operator == GREAT)
		fd = assign_fd_great(minivault, command, file);
	else if (operator == DGREAT)
		fd = assign_fd_dgreat(minivault, command, file);
	else if (operator == LESS)
		fd = assign_fd_less(minivault, command, file);
	if (operator == LESS)
	{
		close_pipes(command->infile_fd, 1);
		command->infile_fd = fd;
	}
	else if (operator == DGREAT || operator == GREAT )
	{
		close_pipes(0, command->outfile_fd);
		command->outfile_fd = fd;
	}
	return (fd);
}
