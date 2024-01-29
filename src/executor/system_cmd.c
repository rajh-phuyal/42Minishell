#include "minishell.h"

size_t	get_list_size(t_word *head)
{
	t_word *current;
	size_t size = 0;

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
	int		i = 0;
	char	**arguments = NULL;

	int list_size = get_list_size(words);
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

t_redir *get_last_token(t_redir *head)
{
	t_redir *current;

	if (!head)
		return (NULL);
	current = head;
	while (current->next)
		current = current->next;
	return (current);
}




void system_command(t_minivault *minivault, t_command *command, int pos)
{
    char *cmd_path;
	
	cmd_path = handle_path(minivault, command->words->word);
	if(!cmd_path)
	{
		close_pipes(minivault, command, pos);
		return ;
	}
    char **arg = get_arguments(command->words);
    pid_t child = fork();
    if (child == -1)
    {
		free(cmd_path); // Free the memory allocated by get_command_path
        return ;
    }
    if (child == 0) // Child process
	{
		set_signals(SIG_STATE_CHILD);
		config_io(minivault, command, pos);
        execve(cmd_path, arg, minivault->env_list);
		error(minivault, CMDNOTFOUND, true, command->words->word, ": ", strerror(errno), NULL); // ? check this later
        // free(cmd_path);
		// free arg
    }
	else // Parent process
	{
        int status;

		set_signals(SIG_STATE_PARENT);
		close_pipes(minivault, command, pos);
        waitpid(child, &status, 0);
        if (WIFEXITED(status))
			set_env(minivault, "?", ft_itoa(WEXITSTATUS(status)), (1 << 1));
		// else
        //     dprintf(2, RED"Child process did not exit normally\n"RESET_COLOR);
    }
	// free arg
}
