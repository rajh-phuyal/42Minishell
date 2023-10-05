
#include "minishell.h"

/* checks the type of token received */
int	token_type(char *token)
{
	(void)token;
	return (1);
}

/* add a token to the linked list of tokens */
void	check_for_tokens(t_minivault *minivault, char *input)
{
	// ls   -l    |    grep  -i "hello world" |    wc  -l
	// CMD  ARG  PIPE   CMD  ARG     ARG     PIPE  CMD  ARG

	add_token(minivault, input, token_type(input));
}

/* atempting to create tokens based on the received input str for the readline */
void	lexer(t_minivault *minivault, char *input)
{
	// jsut a exit command for testing purposes
	if (!ft_strncmp(input, "exit", 5))
	{
		free(input);
		liberation(minivault);
		exit(0);
	}

	// try building the baobab tree, only while testings
	if (!ft_strncmp(input, "build tree", 11))
		grow_baobab(minivault);
	else
		check_for_tokens(minivault, input);
	print_tokens(minivault->tokens);
}
