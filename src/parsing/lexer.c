
#include "minishell.h"

/* add a token to the linked list of tokens */
void	check_for_tokens(t_minivault *minivault, char *input)
{
	add_token(minivault, input);
}

/* atempting to create tokens based on the received input str for the readline */
void	lexer(t_minivault *minivault, char *input)
{
	check_for_tokens(minivault, input);
	print_tokens(minivault->tokens);

	// jsut a exit command for testing purposes
	if (!ft_strncmp(input, "exit", 5))
	{
		free(input);
		exit(0);
	}

	// try building the baobab tree, only while testings
	if (!ft_strncmp(input, "build tree", 11))
		build_baobab(minivault);
}
