
#include "minishell.h"

void    liberate_tokens(t_token *head)
{
    t_token *temp;

    while (head)
    {
        temp = head->next;
        free(head->token);
        free(head);
        head = temp;
    }
}

// void    liberate_baobab(t_baobab *head)
// {
//     t_baobab *temp;

//     while (head)
//     {
//         temp = head->next;
//         free(head);
//         head = temp;
//     }
// }

void    liberation(t_minivault *minivault)
{
    liberate_tokens(minivault->tokens);
    // liberate_baobab(minivault->baobab);
}