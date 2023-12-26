#include "minishell.h"

void	builtin_command(t_minivault	*minivault, t_command *command)
{
	// run builtin commands here
	if (!ft_strncmp(command->words->word, "echo", 5))
		_echo(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "cd", 3))
		_cd(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "pwd", 4))
		_pwd(minivault);
	else if (!ft_strncmp(command->words->word, "export", 7))
		_export(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "unset", 6))
		_unset(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "env", 4))
		_env(minivault);
	else if (!ft_strncmp(command->words->word, "exit", 5))
		_exit_vault(minivault, command->words->next);
	// else
	// 	error("bitch! fuck off! NAC: Not a command");
}