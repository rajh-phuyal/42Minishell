/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:57:13 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:13:45 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	get_list_size(t_word *head)
{
	t_word	*current;
	size_t	size;

	size = 0;
	if (!head)
		return (size);
	current = head;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

static	char	**get_arguments(t_word *words)
{
	int		i;
	int		list_size;
	char	**arguments;

	i = 0;
	arguments = NULL;
	list_size = get_list_size(words);
	arguments = (char **)malloc((list_size + 1) * sizeof(char *));
	if (!arguments)
		return (NULL);
	while (words)
	{
		arguments[i] = words->word;
		words = words->next;
		i++;
	}
	arguments[i] = NULL;
	return (arguments);
}

void	system_command(t_minivault *minivault, \
		t_command *command, int in, int out)
{
	char		**arg;
	t_status	status;

	status = CMDNOTFOUND;
	if (command->status == 0)
	{
		set_signals(SIG_STATE_CHILD);
		arg = get_arguments(command->words);
		catch_fd(minivault, dup2(out, STDOUT_FILENO));
		catch_fd(minivault, dup2(in, STDIN_FILENO));
		close_pipes(in, out);
		close_pipes(command->fd[0], command->fd[1]);
		if (command->exec_path)
			execve(command->exec_path, arg, minivault->env_list);
		error(minivault, FAILURE, true, command->words->word, ": ", \
			"command not executed", NULL);
		status = get_status_owner_can_execute(command->exec_path);
		free(arg);
	}
	liberation(minivault);
	exit(status);
}
