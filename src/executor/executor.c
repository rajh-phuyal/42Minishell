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

void	execute_command(t_minivault *minivault, t_command *command, int pos)
{
	if (!command)
	{
		//wtf happened
	}
	if (command->words)
	{
		if (is_cmd_builtin(minivault->builtin_list, command->words->word))
			builtin_command(minivault, command);
		else
			system_command(minivault, command, pos);
	}
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int pos = -1;
	int i = 0;

	if (!pipeline)
	{
		// deal with it
		return ;
	}
	while (pipeline[++pos])
	{
		execute_command(minivault, pipeline[pos], pos);
	}
}