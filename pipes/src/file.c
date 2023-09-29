#include "../include/pipes.h"

void	open_infile(void)
{
	int	fd;

	fd = open(args()->av[0], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: %s\n", strerror(errno));
		close(fd);
		exit(1);
	}
	data()->infile_fd = fd;
}