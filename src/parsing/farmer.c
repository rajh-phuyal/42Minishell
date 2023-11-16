
#include "minishell.h"

int		find_redirection_type(t_token *token)
{
	if (token->type == REDIRECTION)
	{
		if (!ft_strncmp(token->content, ">>", 2))
			return (DGREAT);
		else if (!ft_strncmp(token->content, "<<", 2))
			return (DLESS);
		else if (!ft_strncmp(token->content, ">", 1))
			return (GREAT);
		else if (!ft_strncmp(token->content, "<", 1))
			return (LESS);
	}
	return (ERROR);
}

int		count_tokens(t_content_type token_type, t_token *tokens)
{
	t_token	*current;
	int i;

	current = tokens;
	i = 0;
	while (current)
	{
		if (current->type == token_type)
			i++;
		current = current->next;
	}
	return (i);
}

void	add_token_back(t_token *list, t_token *token)
{
    t_token *head;

    head = list;
    if (!head)
    {
        head = token;
        return ;
    }
    if (!head->next)
    {
        head->next = token;
        return ;
    }
    while (head->next)
        head = head->next;
    head->next = token;
} 

t_token	*split_list(t_token *list, int index)
{
	t_token *new_list;
	t_token *temp;
	static t_token *current;

	new_list = NULL;
	if(!list)
		return (NULL);
	if (index == 0)
		current = list;
	while (current)
	{
		if (current->type == PIPE)
		{
			current = current->next;
			break ;
		}
		temp = current;
		current = current->next;
		add_token_back(new_list, temp);
	}
	return (new_list);
}

void	grow_baobab(t_minivault	*minivault)
{
	int i;
	int command_count;

	command_count = 1 + count_tokens(PIPE, minivault->tokens);
	minivault->baobab->pipeline = (t_command **)malloc(sizeof(t_command **) * (command_count + 1));
	i = 0;
	while (i < command_count)
	{
		minivault->baobab->pipeline[i]->temp_list = split_list(minivault->tokens, i);
		i++;
	}
}
