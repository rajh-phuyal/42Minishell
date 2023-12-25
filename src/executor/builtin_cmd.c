#include "minishell.h"

static	void	_prep_builtins_data(t_minivault *minivault)
{
	// TODO: prepare the data type necessary for builtins
	//? Eg: for export is a list of key value pairs, for unset its a list of keys
	//? maybe a transformation from the token list to a flat env type of list,
	//? maybe using t_list,
	//* content points to a block of mem tlist_var->content = [[key],[key],\0]
	//* OR tlist_var->content = [[key],[val],[key],[val],\0]
	//? the builtin would just asume that the data type it needs is provided to it.
	(void)minivault;
	return ;
}

static	void	_unprep_builtins_data(t_minivault *minivault)
{
	// TODO: remove the data type added for builtins
	//* there will be a t_list in minivault that will needs to be deallocated
	//* tlist_var->content = [[key],[key],\0]
	//* OR tlist_var->content = [[key],[val],[key],[val],\0]
	//? the builtin would just asume that the data type it needs is provided to it.
	(void)minivault;
	return ;
}

// how to use the same list of builtins here?
void	builtin_command(t_minivault	*minivault, t_command *command)
{
	// run builtin commands here
	_prep_builtins_data(minivault);
	if (!ft_strncmp(command->words->word, "echo", 5))
		_echo(minivault);
	else if (!ft_strncmp(command->words->word, "cd", 3))
		_cd(minivault);
	else if (!ft_strncmp(command->words->word, "pwd", 4))
		_pwd(minivault);
	else if (!ft_strncmp(command->words->word, "export", 7))
		_export(minivault);
	else if (!ft_strncmp(command->words->word, "unset", 6))
		_unset(minivault);
	else if (!ft_strncmp(command->words->word, "env", 4))
		_env(minivault);
	else if (!ft_strncmp(command->words->word, "exit", 5))
		_exit_vault(minivault);
	else
		error("bitch! fuck off! NAC: Not a command");
	_unprep_builtins_data(minivault);
}