#include "minishell.h"

void	liberate_words(t_word *head)
{
	t_word	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	liberate_redir(t_redir *head)
{
	t_redir	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		close(tmp->fd);
		free(tmp);
	}
}

void	cycle_reset(t_minivault *minivault)
{
	// clear out the memory stuffs only necessary for the cycle
	if (minivault->input)
		liberate_vector(minivault->input);
	if (minivault->baobab)
		liberate_baobab(minivault->baobab);
	if (minivault->tokens)
		liberate_tokens(minivault->tokens);
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
}
