#include "minishell.h"

void	init_fds(t_minivault *minivault)
{
	int index;

	index = -1;
	while (++index < FOPEN_MAX)
		minivault->_fds[index] = -1;
}


void	release_fds(t_minivault *minivault)
{
	int index;

	index = -1;
	while (++index < FOPEN_MAX)
	{
		if (minivault->_fds[index] > -1)
			close(minivault->_fds[index]);
	}
}

void	catch_fd(t_minivault *minivault, int fd)
{
	int index;

	index = -1;
	while (++index < FOPEN_MAX)
	{
		if (minivault->_fds[index] == -1)
		{
			minivault->_fds[index] = fd;
			break ;
		}
	}
}
