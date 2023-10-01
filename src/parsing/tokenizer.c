
#include "minishell.h"

t_token *create_new(char *token)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->token = ft_strdup(token);
    new->next = NULL;
    return (new);
}

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
