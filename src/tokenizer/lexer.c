
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
void	check_for_tokens(t_minivault *minivault, int seq)
{
	// ls   -l    |    grep  -i "hello world" |    wc  -l
	// CMD  ARG  PIPE   CMD  ARG     ARG     PIPE  CMD  ARG
	int i = 0;

	while (minivault->input[i])
	{
		add_token(minivault, minivault->input[i], seq + i);
		i++;
	}
}

void	free_vector(char **vector)
{
	int	i;

	i = 0;
	if (!vector)
		return ;
	while (vector[i])
		free(vector[i++]);
	free(vector);
}


/* atempting to create tokens based on the received input str for the readline */
void	lexer(t_minivault *minivault, char *input)
{
	if (!input)
		return ;
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
	else if (!ft_strncmp(input, "var", 3))
		printf("VAL: %s\n", get_env_val(minivault, "PATH"));
	else
	{
		strextract(minivault, input);
		check_for_tokens(minivault, 0); // 0 = name is the sequence number for recognizing the order of the tokens
		free_vector(minivault->input);
	}
	print_tokens(minivault->tokens);
}

