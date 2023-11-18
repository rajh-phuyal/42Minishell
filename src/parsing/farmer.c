
#include "minishell.h"

void    print_redirs(t_redir *head)
{
    while (head)
    {
        printf("OPERATOR: ");
		if (head->operator == GREAT) 
			printf(">");
		else if (head->operator == LESS) 
			printf("<");
		else if (head->operator == DGREAT) 
			printf(">>");
		else if (head->operator == DLESS) 
			printf("<<");
		printf(" | WORD: %s\n",head->word);
        head = head->next;
    }
}
void	print_temp_list(t_minivault *minivault)
{
	int i = 0;

	if (minivault->baobab->pipeline[i]->temp_list)
		printf("\n----------TREE--------\n");
	while (minivault->baobab->pipeline[i])
	{
		if(minivault->baobab->pipeline[i]->temp_list)
		{
			printf("Command: %d", i);
			printf("\n----------------------\n");
			print_tokens(minivault->baobab->pipeline[i]->temp_list);
		}
		printf(RESET_COLOR);
		i++;
	}
}

//-----------------------   ↑ SHITY PRINTS ↑  ----------------------------------

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

void	create_command_list(t_token **list, t_token *token)
{
    t_token *head;
	t_token *temp = (t_token *)malloc(sizeof(t_token));
    if (!temp)
        return ;
	temp->content = token->content;
	temp->type = token->type;
	temp->next = NULL;
    head = (*list);
    if (!head)
    {
        *list = temp;
        return ;
    }
    if (!head->next)
    {
        head->next = temp;
        return ;
    }
    while (head->next)
        head = head->next;
    head->next = temp;
}

t_token	*split_list(t_token* list, t_content_type type)
{
    static t_token* current = NULL;
    t_token* new_list = NULL;

    if (!list)
        return NULL;
    if (current == NULL)
        current = list;
    while (current) 
    {
        if (current->type == type) 
        {
            current = current->next;
			break ;
		}
        create_command_list(&new_list, current);
        current = current->next;
    }
    return (new_list);
}

void	grow_baobab(t_minivault	*minivault)
{
	int i;
	int command_count;

	command_count = 1 + count_tokens(PIPE, minivault->tokens);
	minivault->baobab = (t_baobab *)malloc(sizeof(t_baobab));
	minivault->baobab->pipeline = (t_command **)malloc(sizeof(t_command *) * (command_count + 1));
	minivault->baobab->pipeline[command_count] = NULL;
	i = 0;
	while (i < command_count)
	{
		minivault->baobab->pipeline[i] = (t_command *)malloc(sizeof(t_command));
		if (command_count == 1)
			minivault->baobab->pipeline[i]->temp_list = minivault->tokens;
		else
			minivault->baobab->pipeline[i]->temp_list = split_list(minivault->tokens, PIPE);
		i++;
	}
	i = 0;
	// call_debug(minivault);
	print_temp_list(minivault);
}
