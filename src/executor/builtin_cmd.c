#include "minishell.h"

// how to use the same list of builtins here?
void	builtin_command(t_minivault	*minivault, t_command *command)
{
	// run builtin commands here
	(void) minivault;
	if (!ft_strncmp(command->words->word, "echo", 5))
		// run echo
		_echo(minivault);
	else if (!ft_strncmp(command->words->word, "cd", 3))
		// run cd
		_cd(minivault);
	else if (!ft_strncmp(command->words->word, "pwd", 4))
		// run pwd
		_pwd(minivault);
	else if (!ft_strncmp(command->words->word, "export", 7))
		// run export
		_export(minivault);
	else if (!ft_strncmp(command->words->word, "unset", 6))
		// run unset
		_unset(minivault);
	else if (!ft_strncmp(command->words->word, "env", 4))
		// run env
		_env(minivault);
	else if (!ft_strncmp(command->words->word, "exit", 5))
		// run exit
		_exit(minivault);
	else
		raiseError("bitch! fuck off! NAC: Not a command");
		// run as system_cmd?
}