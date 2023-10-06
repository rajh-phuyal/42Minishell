
#include "minishell.h"

int	init_minivault(t_minivault *minivault)
{
	minivault->envp = NULL;
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
	printf("Minishell initialized\n");
	return (0);
}
