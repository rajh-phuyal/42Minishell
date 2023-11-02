
#include "minishell.h"

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
	// just a exit command for testing purposes
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
		printf("VAL: %s\n", get_env(minivault, "PATH"));
	else
	{
		strextract(minivault, input);
		tokenizer(minivault, 0);
		remove_quotes(minivault);
		print_tokens(minivault->tokens);
		liberate_vector(minivault->input);
	}
}
