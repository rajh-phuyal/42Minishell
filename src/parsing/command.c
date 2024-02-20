#include "minishell.h"

static bool	is_cmd_builtin(char **builtin_list, char *cmd)
{
	int	i;

	i = 0;
	while (builtin_list[i])
	{
		if (!ft_strncmp(cmd, builtin_list[i], ft_strlen(builtin_list[i]) + 1))
			return (true);
		i++;
	}
	return (false);
}

t_command	*init_command(void)
{
	t_command		*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->exec_path = NULL;
	command->words = NULL;
	command->redir_in = NULL;
	command->redir_out = NULL;
}

void	config_command(t_minivault *minivault, t_command *command)
{
	if (command->words)
	{
		command->is_builtin = is_cmd_builtin((char *[]){"echo", "cd", "pwd", \
		"export", "unset", "env", "exit", NULL}, command->words->word);
		if (!command->is_builtin)
			command->exec_path = get_exec_path(minivault, \
			command->words->word);
	}
}

void	process_token(t_minivault *minivault, t_command **command, \
		t_token **current, t_content_type type)
{
	if ((*current)->type == REDIRECTION && \
		((*current)->next->type == LITERAL || \
		(*current)->next->type == QUOTED))
	{
		add_redirection(minivault, command, *current, (*current)->next);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == LITERAL || \
			(*current)->type == QUOTED)
	{
		add_word(&((*command)->words), *current);
		*current = (*current)->next;
	}
}

t_command	*split_list(t_minivault *minivault, t_token *list, \
			t_content_type type)
{
	static t_token	*current = NULL;
	t_command		*command;

	command = init_command();
	if (current == NULL)
		current = list;
	while (current && command && list)
	{
		if (current->type == type)
		{
			current = current->next;
			break ;
		}
		process_token(minivault, &command, &current, type);
	}
	config_command(minivault, command);
	return (command);
}
