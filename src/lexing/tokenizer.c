#include "minishell.h"

/* checks the type of token received */
int	token_type(char *token)
{
	if (!ft_strncmp(token, "|", 1))
		return (PIP);
	if (!ft_strncmp(token, ">", 1))
		return (GREAT);
	if (!ft_strncmp(token, "<", 1))
		return (LESS);
	return (WORD);
}

t_token *create_new(char *token)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->type = token_type(token);
    new->content = ft_strdup(token);
    return (new);
}

// add tokens to the list of tokens
void    add_token(t_minivault *minivault, char *token)
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
    if (!head->next)
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
		add_token(minivault, minivault->input[i]);
		i++;
	}

}