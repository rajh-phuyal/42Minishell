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

void	reset_path(t_minivault *minivault)
{
	int	i;

	i = 0;
	while (minivault->path && minivault->path[i])
	{
		free(minivault->path[i]);
		minivault->path[i++] = NULL;
	}
	if (minivault->path)
		free(minivault->path);
	if (get_env(minivault, "PATH"))
		minivault->path = ft_split(get_env(minivault, "PATH"), ':');
	else
		minivault->path = NULL;
}

void	liberate_baobab(t_baobab *head)
{
	int	i;

	i = 0;
	if (!head)
		return ;
	while (head->pipeline && head->pipeline[i])
	{
		liberate_words(head->pipeline[i]->words);
		liberate_redir(head->pipeline[i]->redir_in);
		liberate_redir(head->pipeline[i]->redir_out);
		free(head->pipeline[i]);
		i++;
	}
	free(head->pipeline);
	free(head);
	head = NULL;
}

void	cycle_reset(t_minivault *minivault)
{
	// clear out the memory stuffs only necessary for the cycle
	// clean_pip_fds(minivault->baobab->)
	if (minivault->input)
		liberate_vector(minivault->input);
	if (minivault->baobab)
		liberate_baobab(minivault->baobab);
	if (minivault->tokens)
		liberate_tokens(minivault->tokens);
	reset_path(minivault);
	minivault->input = NULL;
	minivault->tokens = NULL;
	minivault->baobab = NULL;
}
