#include "minishell.h"

static int	assign_fd_great(t_minivault *minivault, const char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK) != 0)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (owner_can_write(file))
		fd = open(file, O_WRONLY | O_TRUNC);
	else
		error(minivault, REDIRFAIL, true, file, \
		": ", "Permission denied", NULL);
	return (fd);
}

static int	assign_fd_dgreat(t_minivault *minivault, const char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK) != 0)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
	else if (owner_can_write(file))
		fd = open(file, O_WRONLY | O_APPEND);
	else
		error(minivault, REDIRFAIL, true, file, \
		": ", "Permission denied", NULL);
	return (fd);
}

static int	assign_fd_less(t_minivault *minivault, const char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK) != 0)
	{
		error(minivault, REDIRFAIL, true, file, ": ", \
		"No such file or directory", NULL);
		return (fd);
	}
	if (owner_can_read(file))
		fd = open(file, O_RDONLY);
	else
		error(minivault, REDIRFAIL, true, file, \
		": ", "Permission denied", NULL);
	return (fd);
}

int	assign_fd(t_minivault *minivault, t_operation operator, const char *file)
{
	int	fd;

	fd = -1;
	if (operator == GREAT)
		fd = assign_fd_great(minivault, file);
	else if (operator == DGREAT)
		fd = assign_fd_dgreat(minivault, file);
	else if (operator == LESS)
		fd = assign_fd_less(minivault, file);
	return (fd);
}
