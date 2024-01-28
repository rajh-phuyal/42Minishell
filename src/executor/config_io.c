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
		printf("infile fd: %d\n", infile->fd);
		dup2(infile->fd, STDIN_FILENO);
		close(infile->fd);
	}
	if (outfile)
	{
		dup2(outfile->fd, STDOUT_FILENO);
		close(outfile->fd);
	}
}

// reads from the redir in and redirects stdout to pipe[0][1].
void	config_io_first(t_minivault	*minivault, t_command *command)
{
	t_redir	*infile;
	t_redir	*outfile;

	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	if (infile)
	{
		printf("infile fd: %d\n", infile->fd);
		dup2(infile->fd, STDIN_FILENO);
		close(infile->fd); // Close the file descriptor after dup2
	}
	if (outfile)
	{
		dup2(outfile->fd, STDOUT_FILENO);
		close(outfile->fd); // Close the file descriptor after dup2
	}
	else
	{
		close(minivault->baobab->pipe_fd[0][READ]);
		dup2(minivault->baobab->pipe_fd[0][WRITE], STDOUT_FILENO);
		close(minivault->baobab->pipe_fd[0][WRITE]); // Close the file descriptor after dup2
	}
}

// (if redir in is empty) reads from from pipe[i-1][0] and (if redir out is empty) writes to pipe[i][1].
void	config_io_middle(t_minivault	*minivault, t_command *command, int pos)
{
	t_redir	*infile;
	t_redir	*outfile;

	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	// Setup input from the previous pipe if no infile
	if (!infile)
	{
		close(minivault->baobab->pipe_fd[pos - 1][WRITE]); // Close unused write end
		dup2(minivault->baobab->pipe_fd[pos - 1][READ], STDIN_FILENO);
		close(minivault->baobab->pipe_fd[pos - 1][READ]);
	}
	else
	{
		dup2(infile->fd, STDIN_FILENO); //cmd1[]cmd2[]cmd3[]cmd4[]
		close(infile->fd);
	}
	if (!outfile)
	{
		close(minivault->baobab->pipe_fd[pos][READ]); // Close unused read end
		dup2(minivault->baobab->pipe_fd[pos][WRITE], STDOUT_FILENO);
		close(minivault->baobab->pipe_fd[pos][WRITE]);
	}
	else
	{
		dup2(outfile->fd, STDOUT_FILENO);
		close(outfile->fd);
	}
}

// For the last command, redirect stdin from pipes[n-2][0].
void	config_io_last(t_minivault	*minivault, t_command *command)
{
	t_redir	*infile;
	t_redir	*outfile;
	int last_pipe_index;

	infile = get_last_token(command->redir_in);
	outfile = get_last_token(command->redir_out);
	// Setup input from the last pipe if no infile
	if (!infile)
	{
		last_pipe_index = count_tokens(PIPE, minivault->tokens) - 1; // Assuming command_count is the total number of commands
		close(minivault->baobab->pipe_fd[last_pipe_index][WRITE]); // Close unused write end
		dup2(minivault->baobab->pipe_fd[last_pipe_index][READ], STDIN_FILENO);
		close(minivault->baobab->pipe_fd[last_pipe_index][READ]);
	}
	else
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

void	config_io(t_minivault	*minivault, t_command *command, int pos)
{
	if (command->pos == SINGLE)
		config_io_single(minivault, command);
	if (command->pos == FIRST)
		config_io_first(minivault, command);
	if (command->pos == MIDDLE)
		config_io_middle(minivault, command, pos);
	if (command->pos == LAST)
		config_io_last(minivault,command);
}