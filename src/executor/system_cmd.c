#include "minishell.h"

size_t	get_list_size(t_word *head)
{
	t_word	*current;
	size_t	size;

	size = 0;
	if (!head)
		return (size);
	current = head;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	**get_arguments(t_word *words)
{
	int		i;
	int		list_size;
	char	**arguments;

	i = 0;
	arguments = NULL;
	list_size = get_list_size(words);
	arguments = (char **)malloc((list_size + 1) * sizeof(char *));
	if (!arguments)
		return (NULL);
	while (words)
	{
		arguments[i] = words->word;
		words = words->next;
		i++;
	}
	arguments[i] = NULL;
	return (arguments);
}

t_redir	*get_last_token(t_redir *head)
{
	t_redir	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

void	system_command(t_minivault *minivault, t_command *command, int pos)
{
	char	**arg;

	arg = get_arguments(command->words);
	command->pid = fork();
	if (command->pid == 0)
	{
		set_signals(SIG_STATE_CHILD);
		config_io(minivault, command, pos);
		execve(command->exec_path, arg, minivault->env_list);
		error(minivault, CMDNOTFOUND, true, command->words->word, \
		": ", "command not executed", NULL);
		free(arg);
		free(command->exec_path);
		close_pipes(minivault, command, pos);
		liberation(minivault);
		exit(127);
	}
	else
	{
		free(arg);
		free(command->exec_path);
		set_signals(SIG_STATE_PARENT);
		close_pipes(minivault, command, pos);
	}
}
