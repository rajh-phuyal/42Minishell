
#include "minishell.h"

void    print_redirs(t_redir *head)
{
    while (head)
    {
        printf("REDIRECTION: ");
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

void    print_words(t_word *head)
{
    while (head)
    {
        printf("WORD: %s \n", head->word);
        head = head->next;
    }
}

void	print_tree(t_minivault *minivault)
{
	int i = 0;


	printf("\n----------TREE--------\n");
	while (minivault->baobab->pipeline[i])
	{
		if(i != 0)
			printf("\n----------------------\n");
		printf("Command: %d\n", i);
		printf("Command pos: %d", minivault->baobab->pipeline[i]->pos);
		printf("\n----------------------\n");
		// if (minivault->baobab->pipeline[i]->redir_in)
			print_redirs(minivault->baobab->pipeline[i]->redir_in);
		if (minivault->baobab->pipeline[i]->words)
			print_words(minivault->baobab->pipeline[i]->words);
		// if (minivault->baobab->pipeline[i]->redir_out)
			print_redirs(minivault->baobab->pipeline[i]->redir_out);
		printf(RESET_COLOR);
		i++;
	}
}

//-----------------------  ↑ SHITY PRINTS ↑  ----------------------- //

t_command	*split_list(t_token *list, t_content_type type)
{
    static t_token* current = NULL;
	t_command *command = NULL;

	command = (t_command *)malloc(sizeof(t_command));
	command->words = NULL;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->redir_out = NULL;
	if(!command || !list)
        return (NULL);
    if (current == NULL)
        current = list;
    while (current)
    {
        if (current->type == type)
        {
            current = current->next;
			break ;
		}
        if (current && current->next && current->type == REDIRECTION && \
		(current->next->type == LITERAL || current->next->type == QUOTED))
		{
			add_redirection(&command, current, current->next);
			current = current->next->next;
		}
		if (current && (current->type == LITERAL || current->type == QUOTED))
		{
			add_word(&(command->words), current);
			current = current->next;
		}
	}
	return (command);
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

// TODO: Protect Mallocs
void	grow_baobab(t_minivault	*minivault)
{
	int i;
	int command_count;

	command_count = 1 + count_tokens(PIPE, minivault->tokens);
	
	minivault->baobab = (t_baobab *)malloc(sizeof(t_baobab));
	minivault->baobab->pipeline = (t_command **)malloc(sizeof(t_command *) * (command_count + 1));
	while (i < command_count - 1)
	{
		if (pipe(minivault->baobab->pipe_fd[i]) == -1)
		{
			// Handle error
		}
		i++;
	}
	i = 0;
	minivault->baobab->pipeline[command_count] = NULL;
	while (i < command_count)
	{
		minivault->baobab->pipeline[i] = (t_command *)malloc(sizeof(t_command));
		minivault->baobab->pipeline[i] = split_list(minivault->tokens, PIPE);
		if (minivault->baobab->pipeline[i] == NULL) // something is fucked
			break ;
		minivault->baobab->pipeline[i]->pos = (1 + (i > 0)
						+ (i == (command_count - 1)))
						- (2 * (command_count == 1));
		i++;
	}
	i = 0;
	call_debug(minivault);
	print_tree(minivault);
}
