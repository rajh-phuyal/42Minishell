#include "minishell.h"

void	execute_command(t_minivault *minivault, t_command *command, int pos)
{
	if (command->words)
	{
		if (command->is_builtin)
			builtin_command(minivault, command, pos);
		else
			system_command(minivault, command, pos);
	}
}

void	wait_status(t_minivault *minivault, t_command **pipeline)
{
	int	pos;
	int	status;

	pos = -1;
	status = 0;
	if (!pipeline)
		return ;
	while (pipeline && pipeline[++pos])
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			set_env(minivault, "?", ft_itoa(WEXITSTATUS(status)), (1 << 1));
	}
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int	pos;

	pos = -1;
	if (!pipeline)
		return ;
	while (pipeline && pipeline[++pos])
		execute_command(minivault, pipeline[pos], pos);
	wait_status(minivault, pipeline);
}
