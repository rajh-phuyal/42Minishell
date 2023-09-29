#include "../include/pipes.h"

void	get_path(void)
{
	int 	i = 0;
	char	*temp;
	while(args()->env[i])
	{
		if (strncmp(args()->env[i], "PATH=", 5) == 0)
		{
			temp = ft_strdup(args()->env[i] + 5);
			data()->path = ft_split(temp, ':'); // data->cmd is allocated and has to be freed
			free(temp);
			return ;
		}
		i++;
	}
	write(STDERR, "PATH NOT FOUND\n", 15);
	exit(1);
}

void initialize_vars(int ac, char **av, char **env)
{
	data()->pipe_fd[0] = -1;
	data()->pipe_fd[1] = -1;
	data()->infile_fd = -1;
	data()->outfile_fd = -1;
	args()->ac = ac - 1;
	args()->av = av + 1;
	args()->env = env;
	data()->cmd1 = ft_strdup(av[1]); // this has to be changed
	data()->cmd1_path = NULL;

}

void	check_args(void)
{
	if (args()->ac != 4) // this has to change for multiple pipes
	{
		printf("Error: %s\n", strerror(EINVAL));
		exit(1);
	}
	if (pipe(data()->pipe_fd) < 0)
	{
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}
}

void	find_cmd()
{
	char *temp;
	int i = 0;

	while(data()->path[i])
	{
		temp = ft_strjoin(data()->path[i], "/");
		temp = ft_strjoin(temp, data()->cmd1);
		if (access(temp, F_OK) == 0)
		{
			data()->cmd1_path = temp;
			return ;
		}
		free(temp);
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	initialize_vars(ac, av, env);
	check_args();
	get_path();
	open_infile();
	find_cmd();
}