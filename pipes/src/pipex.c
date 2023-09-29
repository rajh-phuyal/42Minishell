#include "../include/pipes.h"

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