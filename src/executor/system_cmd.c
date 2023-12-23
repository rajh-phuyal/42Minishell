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

	if (!words->next)
		return (NULL); // single command with no arguments
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



char	*get_command_path(char **path_list, char *command)
{
	char *temp;
	int i = 0;

	while (path_list && path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		temp = ft_strjoin(temp, command);
		if (access(temp, F_OK) == 0) // returns if the file exists in the path list
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
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
    char *cmd_path = get_command_path(minivault->path, command->words->word);
    char **arg = get_arguments(command->words);
    if (!cmd_path)
        return;
    pid_t child = fork();
    if (child == -1)
    {
		free(cmd_path); // Free the memory allocated by get_command_path
        return;
    }
    if (child == 0) // Child process
	{
		config_io(minivault, command, pos);
        // execve(cmd_path, arg, minivault->env_list);
		execve(cmd_path, arg, NULL);
        perror("Execve failed");
        free(cmd_path);
		// free arg
    }
	else // Parent process
	{
        int status;
        waitpid(child, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status))
            dprintf(2,"Child exited with status %d\n", WEXITSTATUS(status));
		else
            dprintf(2, "Child process did not exit normally\n");
    }
    free(cmd_path);
	// free arg
}
