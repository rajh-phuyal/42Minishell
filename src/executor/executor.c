#include "minishell.h"

bool is_cmd_builtin(char **builtin_list, char *cmd)
{
    int i = 0;

    while (builtin_list[i])
    {
        if (!ft_strncmp(cmd, builtin_list[i], ft_strlen(builtin_list[i]) + 1))
            return (true);
        i++;
    }
    return (false);
}


void	execute_command(t_minivault *minivault, t_command *command, int pos)
{
	(void)pos;
	if (command->words)
	{
		// if (is_cmd_builtin(minivault->builtin_list, command->words->word))
		// 	return ;
		// 	// builtin_command(minivault, command);
		// else
		// system_command(minivault, command, pos);
		builtin_command(minivault, command);
	}
	// TODO: execution with only redirections e.g. $ > file or $ > file >> file2
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int pos = -1;
	if (!pipeline)		// deal with it
		return ;
	while (pipeline[++pos])
		execute_command(minivault, pipeline[pos], pos);
}