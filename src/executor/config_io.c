#include "minishell.h"

void	config_io_single(t_minivault *minivault, t_command *command)
{
	t_redir	*infile;
	t_redir	*outfile;

	(void)minivault;
	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	if (infile)
	{
		dup2(infile->fd, STDIN_FILENO);
		close(infile->fd);
	}
	if (outfile)
	{
		dup2(outfile->fd, STDOUT_FILENO);
		close(outfile->fd);
	}
}

void	config_io_first(t_minivault	*minivault, t_command *command)
{
	t_redir	*infile;
	t_redir	*outfile;

	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	if (infile)
	{
		insert_fd_catcher(minivault, dup2(infile->fd, STDIN_FILENO));
		close(infile->fd);
	}
	if (outfile)
	{
		insert_fd_catcher(minivault, dup2(outfile->fd, STDOUT_FILENO));
		close(outfile->fd);
	}
	else
	{
		close(minivault->baobab->pipe_fd[FIRST_ELEM][READ]);
		insert_fd_catcher(minivault, dup2(minivault->baobab->pipe_fd[FIRST_ELEM][WRITE], STDOUT_FILENO));
		close(minivault->baobab->pipe_fd[FIRST_ELEM][WRITE]);
	}
}

void	config_io_middle(t_minivault	*minivault, t_command *command, int pos)
{
	t_redir	*infile;
	t_redir	*outfile;

	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	if (!infile)
	{
		close(minivault->baobab->pipe_fd[pos - 1][WRITE]);
		insert_fd_catcher(minivault, dup2(minivault->baobab->pipe_fd[pos - 1][READ], STDIN_FILENO));
		close(minivault->baobab->pipe_fd[pos - 1][READ]);
	}
	else
	{
		insert_fd_catcher(minivault, dup2(infile->fd, STDIN_FILENO));
		close(infile->fd);
	}
	if (!outfile)
	{
		close(minivault->baobab->pipe_fd[pos][READ]);
		insert_fd_catcher(minivault, dup2(minivault->baobab->pipe_fd[pos][WRITE], STDOUT_FILENO));
		close(minivault->baobab->pipe_fd[pos][WRITE]);
	}
	else
	{
		insert_fd_catcher(minivault, dup2(outfile->fd, STDOUT_FILENO));
		close(outfile->fd);
	}
}

void	config_io_last(t_minivault	*minivault, t_command *command)
{
	t_redir	*infile;
	t_redir	*outfile;
	int		last_pipe_index;

	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	if (!infile)
	{
		last_pipe_index = count_tokens(PIPE, minivault->tokens) - 1;
		close(minivault->baobab->pipe_fd[last_pipe_index][WRITE]);
		insert_fd_catcher(minivault, dup2(minivault->baobab->pipe_fd[last_pipe_index][READ], STDIN_FILENO));
		close(minivault->baobab->pipe_fd[last_pipe_index][READ]);
	}
	else
	{
		insert_fd_catcher(minivault, dup2(infile->fd, STDIN_FILENO));
		close(infile->fd);
	}
	if (outfile)
	{
		insert_fd_catcher(minivault, dup2(outfile->fd, STDOUT_FILENO));
		close(outfile->fd);
	}
}

void	config_io(t_minivault	*minivault, t_command *command, int pos)
{
	if (command->pos == SINGLE)
		config_io_single(minivault, command);
	if (command->pos == FIRST)
		config_io_first(minivault, command);
	if (command->pos == MIDDLE)
		config_io_middle(minivault, command, pos);
	if (command->pos == LAST)
		config_io_last(minivault, command);
}
