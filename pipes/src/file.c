#include "../include/pipes.h"

void	open_infile(void)
{
	int	fd;

	fd = open(args()->av[0], O_RDONLY);
	if (fd < 0)
	{
		printf("Error 2: %s\n", strerror(errno));
		close(fd);
		exit(1);
	}
	data()->infile_fd = fd;
}

void	open_outfile(void)
{
	int	fd;

	fd = open(args()->av[3], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error 3: %s\n", strerror(errno));
		close(fd);
		exit(1);
	}
	data()->outfile_fd = fd;
}