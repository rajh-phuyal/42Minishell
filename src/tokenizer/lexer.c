
#include "minishell.h"

/* checks the type of token received */
int	token_type(char *token)
{
	(void)token;
	return (1);
}

// int	temp_token_recon(char *token)
// {

// }

// void	check_for_tokens(t_minivault *minivault, int seq)
// {
// 	// ls   -l    |    grep  -i "hello world" |    wc  -l
// 	// CMD  ARG  PIPE   CMD  ARG     ARG     PIPE  CMD  ARG
// }

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

void look_for_compound(t_token *token, char target)
{
	t_token *current;

	current = token;
	while (current && current->next)
	{
		if (current->token[0] == target)
		{
			if (ft_strlen(current->token) == 1 && ft_strlen(current->next->token) == 1)
			{
				if (current->token[0] == current->next->token[0])
				{
					current->token = ft_strjoin(current->token, current->next->token);
					remove_token(token, current->next);
					return ;
				}
			}
		}
		current = current->next;
	}
}

void look_for_compounds(t_token *token)
{
	look_for_compound(token, '<');
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
	else
	{
		strextract(minivault, input);
		tokenizer(minivault, 0); // 0 = name is the sequence number for recognizing the order of the tokens
		look_for_compounds(minivault->tokens); // compounds <<, >>, and later ... &&, ||
		free_vector(minivault->input);
	}
	printf(GREEN"------------OUTPUT_LIST-------------\n");
	print_tokens(minivault->tokens);
	printf(RESET_COLOR);
}

