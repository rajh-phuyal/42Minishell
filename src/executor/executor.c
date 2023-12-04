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

void	execute_command(t_minivault *minivault, t_command *command, t_cmd_pos pos)
{
	if(!command->words && !command->redir_in && !command->redir_out)
	{
		//wtf happened
	}
	if (command->redir_in)
		// setup redirction input
	if (command->redir_out)
		// setup redirection output
	if (command->words)
	{
		if (is_cmd_builtin(minivault->builtin_list, command->words->word))
			builtin_command(minivault, command);
		else
			system_command(minivault, command);
	}
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int count = 0;
	int i = 0;

	if (!pipeline)
	{
		// deal with it
		return ;
	}
	if (pipeline[0] && pipeline[0]->pos == SINGLE) // * SINGLE CMD EXECUTION
		execute_single_command(minivault, pipeline[0]); // dont fork if is single command and builtin
	else
	{
		while (pipeline[count])
		{
			if (pipeline[count]->pos == FIRST)
				execute_command(minivault, pipeline[count++], FIRST);
			while (pipeline[count] && pipeline[count]->pos == MIDDLE)
				execute_command(minivault, pipeline[count++], MIDDLE);
			if (pipeline[count] && pipeline[count]->pos == LAST)
				execute_command(minivault, pipeline[count++], LAST);
		}
	}
}