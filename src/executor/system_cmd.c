/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:19:02 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:19:04 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_list_size(t_word *head)
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

char	**get_arguments(t_word *words)
{
	int		i;
	int		list_size;
	char	**arguments;

	i = 0;
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

t_redir	*get_last_token(t_redir *head)
{
	t_redir	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

void	system_command(t_minivault *minivault, t_command *command, int pos)
{
	char	*cmd_path;
	char	**arg;
	int		status;
	pid_t	child;

	cmd_path = handle_path(minivault, command->words->word);
	if (!cmd_path)
	{
		close_pipes(minivault, command, pos);
		return ;
	}
	arg = get_arguments(command->words);
	child = fork();
	if (child == -1)
	{
		free(cmd_path);
		return ;
	}
	if (child == 0)
	{
		set_signals(SIG_STATE_CHILD);
		config_io(minivault, command, pos);
		execve(cmd_path, arg, minivault->env_list);
		perror(RED"Execve failed"RESET_COLOR);
		free(cmd_path);
		// free arg
	}
	else
	{
		free(arg);
		free(cmd_path);
		set_signals(SIG_STATE_PARENT);
		close_pipes(minivault, command, pos);
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			set_env(minivault, "?", ft_itoa(WEXITSTATUS(status)), (1 << 1));
	}
}
