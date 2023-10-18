
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

void	trim_string(char *str, int len) 
{
	if (len >= 2) 
	{
		str[len - 1] = '\0';
		ft_memmove(str, str + 1, len);
    }
}

// removes quotes from the end and the begginig of each token
void remove_quotes(t_minivault *minivault)
{
	t_token	*current;
	size_t	len;

	current = minivault->tokens;
	while (current)
	{
		len = ft_strlen(current->token);
		if (len >= 2)
		{
			if (is_double_quote(current->token[0]) && is_double_quote(current->token[len - 1]))
				trim_string(current->token, len);
			if (is_single_quote(current->token[0]) && is_single_quote(current->token[len - 1]))
				trim_string(current->token, len);
		}
		current = current->next;
	}
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
		tokenizer(minivault, 0);
		remove_quotes(minivault); // 0 = name is the sequence number for recognizing the order of the tokens
		free_vector(minivault->input);
	}
	printf(GREEN"------------OUTPUT_LIST-------------\n");
	print_tokens(minivault->tokens);
	printf(RESET_COLOR);
}

