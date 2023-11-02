
#include "minishell.h"

void	liberate_vector(char **vector)
{
	int	i;

	i = 0;
	if (!vector)
		return ;
	while (vector && vector[i])
	{
		free(vector[i]);
		vector[i++] = NULL;
	}
}

// liberates the memory allocated for the tokens
void	liberate_tokens(t_token *head)
{
    t_token *tmp;

	if (!head)
		return ;
    while (head)
    {
        tmp = head->next;
        free(head->token);
        free(head);
        head = tmp;
    }
}

void	liberate_envs(t_envs *head)
{
    t_envs *tmp;

	if (!head)
		return ;
    while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

// void	liberate_baobab(t_baobab *head)
// {
//     t_baobab *temp;

//     while (head)
//     {
//         temp = head->next;
//         free(head);
//         head = temp;
//     }
// }

// liberates the memory allocated for the tokens and the baobab tree
void    liberation(t_minivault *minivault)
{
	if (minivault->input)
		liberate_vector(minivault->input);
	if (minivault->envs)
		liberate_envs(minivault->envs);
	if (minivault->tokens)
 		liberate_tokens(minivault->tokens);
	// if (minivault->baobab)
	// 	liberate_baobab(minivault->baobab);
}