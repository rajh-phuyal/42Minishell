/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:35 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 00:42:02 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	execute_command(t_minivault *minivault, t_command *command, int in, int out)
{
	// if (check_redirs(command->redir_in) == false || \
	// 	check_redirs(command->redir_out) == false)
	// {
	// 	close_pipes(minivault, command, pos);
	// 	command->status = 1;
	// 	return ;
	// }
	if (command->words)
	{
		if (command->is_builtin)
			builtin_command(minivault, command, in, out);
		else
			system_command(minivault, command, in, out);
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
		if (pipeline[pos]->status != 0)
			set_env(minivault, "?", ft_itoa(pipeline[pos]->status), (1 << 1));
		else
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				set_env(minivault, "?", ft_itoa(WEXITSTATUS(status)), (1 << 1));
		}
	}
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int	pos;
	int in;
	int out;

	pos = -1;
	if (!pipeline)
		return ;
	in = STDIN_FILENO;
	while (pipeline[++pos])
	{
		if (pipeline[pos + 1] && pipe(pipeline[pos]->fd) == -1)
			exit(0);
		out = pipeline[pos]->fd[1];
		if (pipeline[pos]->outfile_fd != -1)
		{ 
			close_pipes(0, out);
			out = pipeline[pos]->outfile_fd;
		}
		if (pipeline[pos]->infile_fd != -1)
			in = pipeline[pos]->infile_fd;
		execute_command(minivault, pipeline[pos], in, out);
		in = pipeline[pos]->fd[0];
	}
	wait_status(minivault, pipeline);
}
