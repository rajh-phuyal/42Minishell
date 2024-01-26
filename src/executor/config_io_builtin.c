#include "minishell.h"

int	config_io_single_output(t_minivault *minivault, t_command *command)
{
	int		fd;
	t_redir	*outfile;

	(void)minivault;
	fd = STDOUT_FILENO;
	outfile = get_last_token(command->redir_in);
	if (outfile)
		fd = outfile->fd;
	return (fd);
}

int	config_io_first_output(t_minivault	*minivault, t_command *command)
{
	int	fd;
	t_redir	*outfile;

	fd = STDOUT_FILENO;
	outfile = get_last_token(command->redir_out);
	if (outfile)
		fd = outfile->fd;
	else
	{
		// close(minivault->baobab->pipe_fd[0][READ]);
		fd = minivault->baobab->pipe_fd[0][WRITE];
	}
	return (fd);
}

int	config_io_middle_output(t_minivault	*minivault, t_command *command, int pos)
{
	int	fd;
	t_redir	*outfile;

	(void)minivault;
	fd = STDOUT_FILENO;
	outfile = get_last_token(command->redir_out);
	if (outfile)
		fd = outfile->fd;
	else
	{
		// close(minivault->baobab->pipe_fd[pos][READ]);
		fd = minivault->baobab->pipe_fd[pos][WRITE];
	}
	return (fd);
}

int	config_io_last_output(t_minivault	*minivault, t_command *command)
{
	int	fd;
	t_redir	*outfile;

	(void)minivault;
	fd = STDOUT_FILENO;
	outfile = get_last_token(command->redir_out);
	if (outfile)
		fd = outfile->fd;
	return (fd);
}

int	config_io_builtin(t_minivault *minivault, t_command *command, int pos)
{
	int fd;

	fd = STDOUT_FILENO;
	if (command->pos == SINGLE)
		fd = config_io_single_output(minivault, command);
	else if (command->pos == FIRST)
		fd = config_io_first_output(minivault, command);
	else if (command->pos == MIDDLE)
		fd = config_io_middle_output(minivault, command, pos);
	else if (command->pos == LAST)
		fd = config_io_last_output(minivault,command);
	return(fd);
}