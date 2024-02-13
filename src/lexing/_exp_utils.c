#include "minishell.h"

char	*exe_concat(char *prev, ...)
{
	va_list	args;
	char	*_built;
	// ! dummy is undefined
	va_start(args, dummy);
	_built = concat_all(args);
	va_end(args);
	if (prev)
		free(prev);
	return (_built);
}
