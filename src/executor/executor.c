#include "minishell.h"

bool	check_redirs(t_redir *head)
{
	t_redir	*current;

	if (!head)
		return (true);
	current = head;
	while (current)
	{
		if (current->fd == -1)
			return (false);
		current = current->next;
	}
	return (true);
}

void	execute_command(t_minivault *minivault, t_command *command, int pos)
{
	if (check_redirs(command->redir_in) == false || \
		check_redirs(command->redir_out) == false)
	{
		close_pipes(minivault, command, pos);
		return ;
	}
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
