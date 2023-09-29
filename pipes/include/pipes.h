#ifndef PIPES_H
# define PIPES_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

# define STDIN  0
# define STDOUT 1
# define STDERR 2

typedef struct s_args
{
	int		ac;
	char	**av;
	char	**env;	
}			t_args;

typedef struct s_data
{
	char	*cmd1_path;
	char	*cmd1;
	char	*cmd2;
	char	**path;
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
}			t_data;

t_data	*data(void);
t_args	*args(void);
void	open_infile(void);

#endif