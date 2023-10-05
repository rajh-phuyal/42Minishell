
#include "minishell.h"

t_token *create_new(char *token, int type)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->type = type;
    new->token = ft_strdup(token);
    return (new);
}

// add tokens to the list of tokens
void    add_token(t_minivault *minivault, char *token, int type)
{
    t_token *head;
    t_token *token_node;

    head = minivault->tokens;
    token_node = create_new(token, type);
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
    node->token = temp->token;
    node->next = temp->next;
    free(temp);
}
