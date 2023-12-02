#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <unistd.h>

void	executor(t_minivault *minivault, t_command **pipeline);

#endif