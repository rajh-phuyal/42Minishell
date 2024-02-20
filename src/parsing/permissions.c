#include "minishell.h"

bool	owner_can_execute(const char *file_path)
{
	struct stat	statbuf;

	return (access(file_path, F_OK) == 0 && \
			access(file_path, X_OK) == 0 && \
			stat(file_path, &statbuf) == 0 && \
			S_ISREG(statbuf.st_mode) && \
			(statbuf.st_mode & S_IXUSR));
}

bool	owner_can_write(const char *file_path)
{
	struct stat	statbuf;

	return (access(file_path, F_OK) == 0 && \
			access(file_path, W_OK) == 0 && \
			stat(file_path, &statbuf) == 0 && \
			S_ISREG(statbuf.st_mode) && \
			(statbuf.st_mode & S_IWUSR));
}

bool	owner_can_read(const char *file_path)
{
	struct stat	statbuf;

	return (access(file_path, F_OK) == 0 && \
			access(file_path, R_OK) == 0 && \
			stat(file_path, &statbuf) == 0 && \
			S_ISREG(statbuf.st_mode) && \
			(statbuf.st_mode & S_IRUSR));
}
