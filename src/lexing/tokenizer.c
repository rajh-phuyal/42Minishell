#include "minishell.h"

bool is_quoted(char *token)
{
	size_t len;

	len = ft_strlen(token);
	if (len >= 2)
	{
		if (is_double_quote(token[0]) && is_double_quote(token[len - 1]))
			return(true);
		else if (is_single_quote(token[0]) && is_single_quote(token[len - 1]))
			return(true);
	}
	return(false);
}

// checks the type of token received
int	token_type(char *token)
{
	if (!ft_strncmp(token, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(token, ">", 1 ) || !ft_strncmp(token, "<", 1) || \
			!ft_strncmp(token, ">>", 2 ) || !ft_strncmp(token, "<<", 2) )
		return (REDIRECTION);
	else if (is_quoted(token))
		return (QUOTED);
	return (LITERAL);
}

t_token *create_new(char *token)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->type = token_type(token);
    new->content = token;
    return (new);
}

// add tokens to the list of tokens
void	add_token(t_minivault *minivault, char *token)
{
    t_token *head;
    t_token *token_node;

    head = minivault->tokens;
    token_node = create_new(token);
    if (!head)
    {
        minivault->tokens = token_node;
        return ;
    }
    if (head && !head->next)
    {
        head->next = token_node;
        return ;
    }
    while (head->next)
        head = head->next;
    head->next = token_node;
}

// remove the token from the list of tokens
void    remove_token(t_token *head, t_token *node)
{
    t_token *temp;

    if (!node)
        return ;
    if (!node->next)
    {
        while (head->next != node)
            head = head->next;
        free(node);
        head->next = NULL;
        return ;
    }
    temp = node->next;
    node->content = temp->content;
    node->next = temp->next;
    free(temp);
}

void	tokenizer(t_minivault *minivault, int seq)
{
	int i = 0;

	(void)seq;
	// ? what is seq for?
	while (minivault->input[i])
	{
        if (minivault->input[i] && \
            !(minivault->input[i][FIRST_ELEM] == PLACEHOLDER[FIRST_ELEM]))
		    add_token(minivault, minivault->input[i]);
		i++;
	}
}