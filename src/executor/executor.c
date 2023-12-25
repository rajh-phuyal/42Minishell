#include "minishell.h"

bool	is_cmd_builtin(char **builtin_list, char *cmd)
{
	int i = -1;

	while (builtin_list[++i])
	{
		if (builtin_list[i] && !ft_strncmp(cmd, builtin_list[i], 1 + ft_strlen(builtin_list[i])))
			return (true);
	}
	return (false);
}

// TODO: deal with redirections

void	execute_command(t_minivault *minivault, t_command *command)
{
	if (command->words != NULL)
	{
		if (pipe(minivault->pipe_fd) < 0)
		{
			// pipe failed for some reason
			return ;
		}
		if (is_cmd_builtin(minivault->builtin_list, command->words->word) == true)
			builtin_command(minivault, command);
		else
			system_command(minivault, command);
	}
	if (command->redirects != NULL)
	{

	}
	// TODO: execution with only redirections e.g. $ > file or $ > file >> file2
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int count = -1;
	int i = 0;
	if (!pipeline)
	{
		// deal with it
		return ;
	}
	if (pipeline[0] && !pipeline[1])
		execute_single_command(minivault, pipeline[0]); // NO FORK
	else
	{
		while (pipeline[++count])
			execute_command(minivault, pipeline[count]);
	}
}