
#include "minishell.h"

bool	is_cmd_builtin(char **builtin_list, char *cmd)
{
	int i = -1;

	while (builtin_list[++i])
	{
		if (builtin_list[i] && !ft_strncmp(cmd, builtin_list[i], ft_strlen(builtin_list[i])))
			return (true);
	}
	return (false);
}

char	*get_command_path(char *path_list, char *command)
{
	char *temp;
	int i = 0;
	if (!path_list)
	{
		//path_list is empty deal with it
		return ;
	}
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		temp = ft_strjoin(temp, command);
		if (access(temp, F_OK) == 0) // returns if the file exists in the path list
			return (temp);
		free(temp);
		i++;
	}
	// command doesnt exit
}

void	builtin_command(t_minivault	*minivault, t_command *command)
{
	// run builtin commands here
	(void) command;
	(void) minivault;
}

void	system_command(t_minivault	*minivault, t_command *command)
{
	pid_t	child;
	char	*cmd_path;

	cmd_path = get_command_path(minivault->path, command->words);
	if (!cmd_path)
	{
		// path list is fucked or the cmd doesnt exist
		return ;
	}
	child = fork();
	if (child == -1)
	{
		// fork failed
		// deal with it
		return ;
	}
	if (child == 0)
	{
			close(minivault->pipe_fd[0]); // close the read end of the pipe
			dup2(minivault->pipe_fd[1], STDOUT_FILENO); //redirect stdout to the write end of the pipe
			if (execve())
	}


}

/*
void	child1(void)
{
	pid_t	child_1;

	child_1 = fork();
	if (child_1 == -1)
	{
		perror("In child 1 fork error");
		exit(EXIT_FAILURE);
	}
	else if (child_1 == 0)
	{
		open_infile();
    	close(data()->pipe_fd[0]);
    	dup2(data()->pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to the write end of the pipe
		dup2(data()->infile_fd, STDIN_FILENO);
    	if (execve(data()->cmd1_path, ft_split(data()->cmd1, ' '), args()->env) == -1) 
		{
    	    perror("Error executing command1");
    	    exit(EXIT_FAILURE); // Explicitly exit the child process on error
    	}
	}
}
*/

// TODO: deal with redirections

void	execute_command(t_minivault *minivault, t_command *command)
{
	if (command->words != NULL)
	{
		if (pipe(minivault->pipe_fd) < 0)
		{
			// pipe failed for some reason
			return ;
		}
		if (is_cmd_builtin(minivault->builtin_list, command->words->word) == true)
			builtin_command(minivault, command);
		else
			system_command(minivault, command);
	}
	if (command->redirects != NULL)
	{

	}
	// TODO: execution with only redirections e.g. $ > file or $ > file >> file2	
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int i = -1;

	while (pipeline[++i])
		execute_command(minivault, pipeline[i]);
}

/*
void	child1(void)
{
	pid_t	child_1;

	child_1 = fork();
	if (child_1 == -1)
	{
		perror("In child 1 fork error");
		exit(EXIT_FAILURE);
	}
	else if (child_1 == 0)
	{
		open_infile();
    	close(data()->pipe_fd[0]);
    	dup2(data()->pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to the write end of the pipe
		dup2(data()->infile_fd, STDIN_FILENO);
    	if (execve(data()->cmd1_path, ft_split(data()->cmd1, ' '), args()->env) == -1) 
		{
    	    perror("Error executing command1");
    	    exit(EXIT_FAILURE); // Explicitly exit the child process on error
    	}
	}
}

void	child2(void) 
{
	pid_t	child_2;

	child_2 = fork();

	if (child_2 == -1)
	{
		perror("In child 2 fork error");
		exit(EXIT_FAILURE);
	}
	else if (child_2 == 0)
	{
		open_outfile();
		close(data()->pipe_fd[1]);
    	dup2(data()->pipe_fd[0], STDIN_FILENO);  // Redirect stdin to the read end of the pipe
		dup2(data()->outfile_fd, STDOUT_FILENO);
    	if (execve(data()->cmd2_path, ft_split(data()->cmd2, ' '), args()->env) == -1)
		{
    		perror("Error executing command2");
  	    	exit(EXIT_FAILURE); // Explicitly exit the child process on error
    	}
	}
}

void	pipex(void)
{
	if (pipe(data()->pipe_fd) < 0)
	{
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}
	child1();
	child2();
	close(data()->pipe_fd[0]);
	close(data()->pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}
*/