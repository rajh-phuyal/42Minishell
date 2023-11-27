#include "minishell.h"

void    clean_exit(t_minivault *minivault)
{
    liberation(minivault);
    exit(minivault->error->status);
}