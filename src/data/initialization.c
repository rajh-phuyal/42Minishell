
#include "minishell.h"

int	init_minivault(t_minivault *minivault)
{
	minivault->envp = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	write(1, "Minishell initialized\n", 22);
	return (0);
}
