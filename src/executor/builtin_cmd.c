#include "minishell.h"

void	builtin_command(t_minivault	*minivault, t_command *command, int pos)
{
	int	fd;
	int	_stat;

	_stat = -1;
	set_signals(SIG_STATE_CHILD_BUILTIN);
	fd = config_io_builtin(minivault, command, pos);
	if (!ft_strncmp(command->words->word, "echo", 5))
		_echo(minivault, command->words->next, fd);
	else if (!ft_strncmp(command->words->word, "cd", 3))
		_stat = _cd(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "pwd", 4))
		_pwd(minivault, fd);
	else if (!ft_strncmp(command->words->word, "export", 7))
		_export(minivault, command->words->next, fd);
	else if (!ft_strncmp(command->words->word, "unset", 6))
		_unset(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "env", 4))
		_env(minivault, fd);
	else if (!ft_strncmp(command->words->word, "exit", 5))
		_exit_vault(minivault, command->words->next, fd);
	if (_stat >= 0)
		set_env(minivault, PREVEXITSTAT, ft_itoa(_stat), (1 << 1));
	close_pipes(minivault, command, pos);
}