/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:01 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 16:50:42 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_command	*init_command(void)
{
	t_command		*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	command->outfile_fd = -1;
	command->infile_fd = -1;
	command->fd[0] = 0;
	command->fd[1] = 1;
	return (command);
}

static void	config_command(t_minivault *minivault, t_command *command)
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

static void	process_token(t_minivault *minivault, t_command **command, \
		t_token **current)
{
	if ((*current)->type == REDIRECTION && \
		((*current)->next->type == LITERAL || \
		(*current)->next->type == QUOTED))
	{
		add_redirection(minivault, command, *current, (*current)->next);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == LITERAL || (*current)->type == QUOTED)
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
	if (!command)
		return (NULL);
	if (current == NULL)
		current = list;
	while (current && command && list)
	{
		if (current->type == type)
		{
			current = current->next;
			break ;
		}
		process_token(minivault, &command, &current);
	}
	config_command(minivault, command);
	return (command);
}
