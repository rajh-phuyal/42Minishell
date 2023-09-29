#include "../include/pipes.h"

t_args *args(void)
{
	static t_args args;

	return (&args);
}

t_data *data(void)
{
	static t_data data;

	return (&data);
}