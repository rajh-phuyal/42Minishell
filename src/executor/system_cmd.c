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
	t_word	*current;
	int	i = 0;
	char	**arguments = NULL;

	if (!words)
		return (NULL); // list is empty something is fucked
	if (words->next == NULL)
		return (NULL); // single command with no arguments
	arguments = (char**)malloc(get_list_size(words) * sizeof(char *));
	if (!arguments)
		return (NULL);
	current = words->next; // to skip the command name wich is the first node
	while (current)
	{
        arguments[i++] = strdup(current->word);
        current = current->next;
    }
	arguments[i] = NULL;
	return (arguments);
}

char	*get_command_path(char *path_list, char *command)
{
	char *temp;
	int i = 0;
	if (!path_list)
	{
		//path_list is empty deal with it
		return ;
	}
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		temp = ft_strjoin(temp, command);
		if (access(temp, F_OK) == 0) // returns if the file exists in the path list
			return (temp);
		free(temp);
		i++;
	}
	// command doesnt exit
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

void	system_command(t_minivault	*minivault, t_command *command, int pos)
{
	pid_t	child;
	char	*cmd_path;

	cmd_path = get_command_path(minivault->path, command->words);
	if (!cmd_path)
	{
		// path list is fucked or the cmd doesnt exist
		return ;
	}
	child = fork();
	if (child == -1)
	{
		// fork failed deal with it
		return ;
	}
	if (child == 0)
	{
			// dup2(infiles, STDIN_FILENO);
			// TODO: create 2d array with the command and the options
			if (execve(cmd_path, get_arguments(command->words), minivault->env_list) == -1)
			{
				// execve failed 
				// deal with the error
				return ;
			}
	}


}