
#include "minishell.h"

/* checks the type of token received */
int	token_type(char *token)
{
	(void)token;
	return (1);
}

// int	temp_token_recon(char *token)
// {
// 	// ls   -l

// }

/* add a token to the linked list of tokens */
void	check_for_tokens(t_minivault *minivault, char *input, int seq)
{
	// ls   -l    |    grep  -i "hello world" |    wc  -l
	// CMD  ARG  PIPE   CMD  ARG     ARG     PIPE  CMD  ARG

	add_token(minivault, input, seq);
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
	{
		printf("INPUT: %s\n", input);
		strextract(minivault, input); // TODO: Fix this
		check_for_tokens(minivault, input, 0); // 0 = name is the sequence number for recognizing the order of the tokens
	}
	print_tokens(minivault->tokens);
}
