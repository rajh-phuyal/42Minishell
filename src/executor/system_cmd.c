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

char	*get_command_path(char **path_list, char *command)
{
	char	*temp;
	char	*freeable;
	int		i;

	i = 0;
	while (path_list && path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		freeable = temp;
		temp = ft_strjoin(temp, command);
		free(freeable);
		if (access(temp, F_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
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
	int		status;
	char	*cmd_path;
	pid_t	child;
	char	**arg;

	cmd_path = get_command_path(minivault->path, command->words->word);
	if (!cmd_path && !get_env(minivault, "PATH"))
	{
		error(minivault, FAILURE, true, command->words->word, \
			": ", "No such file or directory", NULL);
		close_pipes(minivault, command, pos);
		return ;
	}
	else if (!cmd_path)
	{
		error(minivault, CMDNOTFOUND, true, command->words->word, \
			": ", "command not found", NULL);
		close_pipes(minivault, command, pos);
		return ;
	}
	arg = get_arguments(command->words);
	child = fork();
	if (child == -1)
	{
		free(cmd_path);
		return ;
	}
	if (child == 0)
	{
		set_signals(SIG_STATE_CHILD);
		config_io(minivault, command, pos);
		execve(cmd_path, arg, minivault->env_list);
		perror(RED"Execve failed"RESET_COLOR);
		free(arg);
		free(cmd_path);
		close_pipes(minivault, command, pos);
		liberation(minivault);
	}
	else
	{
		free(arg);
		free(cmd_path);
		set_signals(SIG_STATE_PARENT);
		close_pipes(minivault, command, pos);
		waitpid(child, &status, 0); // ! FIX ME parent should execute everything and wait for the childs after it
		if (WIFEXITED(status))
			set_env(minivault, "?", ft_itoa(WEXITSTATUS(status)), (1 << 1));
	}
}
