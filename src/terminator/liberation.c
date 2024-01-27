
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
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	liberate_baobab(t_baobab *head)
{
	int	i;

	i = 0;
	if (!head)
		return ;
	while (head->pipeline[i])
	{
		liberate_words(head->pipeline[i]->words);
		liberate_redir(head->pipeline[i]->redir_in);
		liberate_redir(head->pipeline[i]->redir_out);
		free(head->pipeline[i]);
		head->pipeline[i++] = NULL;
	}
	free(head);
	head = NULL;
}

// liberates the memory allocated for the tokens and the baobab tree
void    liberation(t_minivault *minivault)
{
	cycle_reset(minivault);
	if (minivault->path)
		liberate_vector(minivault->path);
	if (minivault->envs)
		liberate_envs(minivault->envs);
}