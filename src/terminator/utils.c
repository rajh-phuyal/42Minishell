#include "minishell.h"

void	clean_exit(t_minivault *minivault, int status)
{
    liberation(minivault);
    exit(status);
}