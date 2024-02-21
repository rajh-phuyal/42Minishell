#include "minishell.h"

static void	liberate_words(t_word *head)
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

void	liberate_command(t_command *command)
{
	if (!command)
		return ;
	liberate_words(command->words);
	liberate_redir(command->redir_in);
	liberate_redir(command->redir_out);
	if (command->exec_path)
		free(command->exec_path);
	free(command);
}
