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
// TODO: handle tokens with only ""
void remove_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2)
	{
		if (is_double_quote(str[0]) && is_double_quote(str[len - 1]))
			trim_string(str, len);
		else if (is_single_quote(str[0]) && is_single_quote(str[len - 1]))
			trim_string(str, len);
	}
}

t_word *create_word_node(t_token *token)
{
	t_word *word;

	if (!token || !(token->type == LITERAL || token->type == QUOTED))
		return (NULL);
	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	if (token->type == QUOTED)
		remove_quotes(token->content);
	word->word = token->content;
	word->next = NULL;
	return (word);
}

void	add_word(t_word **word_list, t_token *token)
{
	t_word	*word;
	t_word	*head;

	word = NULL;
	if (token)
		word = create_word_node(token);
	if (!word) // something is fucked;
		return ;
	head = (*word_list);
	if (!head)
	{
		*word_list = word;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = word;
}