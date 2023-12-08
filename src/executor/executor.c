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

void	setup_pipes(t_command *command)
{
	//if (!command->pos)
		// wtf happended panic
	if (command->pos == SINGLE)
	{
		command->pipe_config[0] = false;
		command->pipe_config[1] = false;
	}
	else if (command->pos == FIRST)
	{
		command->pipe_config[0] = false;
		command->pipe_config[1] = true;
	}
	else if (command->pos == MIDDLE)
	{
		command->pipe_config[0] = true;
		command->pipe_config[1] = true;
	}
	else if (command->pos == LAST)
	{
		command->pipe_config[0] = true;
		command->pipe_config[1] = false;
	}
}

void	execute_command(t_minivault *minivault, t_command *command)
{
	if(!command)
	{
		//wtf happened
	}
	setup_pipes(command); // if there is input dont read from previous pipe, if there is an outfile dont write to the next pipe
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
			execute_command(minivault, pipeline[count++]);
	}
}