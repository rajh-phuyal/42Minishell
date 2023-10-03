#ifndef MULTI_PIPES_H
# define MULTI_PIPES_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_args
{
	int		ac;
	char	**av;
	char	**env;
}			t_args;

typedef	struct s_data
{
	t_args		args;
		
}

#endif