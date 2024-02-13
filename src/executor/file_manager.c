#include "minishell.h"

void	init_fds(int *fds)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
		fds[i++] = -1;
}

void	insert_fd(int *fds, int fd)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		if (fds[i] == -1)
		{
			fds[i] = fd;
			break ;
		}
		i++;
	}
}

void	clean_fds(int *fds)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		if (fds[i] != -1)
			close(fds[i]);
		i++;
	}
}
