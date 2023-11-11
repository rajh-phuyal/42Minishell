
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
		len = ft_strlen(current->content);
		if (len >= 2)
		{
			if (is_double_quote(current->content[0]) && is_double_quote(current->content[len - 1]))
				trim_string(current->content, len);
			else if (is_single_quote(current->content[0]) && is_single_quote(current->content[len - 1]))
				trim_string(current->content, len);
		}
		current = current->next;
	}
}
/* atempting to create tokens based on the received input str for the readline */
void	lexer(t_minivault *minivault, char *input)
{
	if (!input)
		return ;
	strextract(minivault, input);
	tokenizer(minivault, 0);
	// remove_quotes(minivault);
}
