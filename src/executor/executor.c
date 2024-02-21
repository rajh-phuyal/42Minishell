/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:35 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 18:27:40 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int in, int out)
{
	if (in != -1 && in != STDIN_FILENO)
		close(in);
	if (out != -1 && out != STDOUT_FILENO)
		close(out);
}

static void	execute_command(t_minivault *minivault, \
			t_command *command, int in, int out)
{
	if (command->words)
	{
		if (minivault->cmd_count == 1 && command->is_builtin)
			builtin_command(minivault, command, in, out);
		else
		{
			command->pid = fork();
			if (command->pid == 0)
			{
				if (command->is_builtin)
				{
					builtin_command(minivault, command, in, out);
					close(command->fd[0]);
					close_pipes(in, out);
					liberate_vector(minivault->input);
					liberation(minivault);
					exit(SUCCESS);
				}
				else
					system_command(minivault, command, in, out);
			}
		}
	}
	close_pipes(in, out);
	set_signals(SIG_STATE_PARENT);
}

static void	wait_status(t_minivault *minivault, t_command **pipeline)
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
	int	in;
	int	out;

	pos = -1;
	if (!pipeline)
		return ;
	in = STDIN_FILENO;
	while (pipeline[++pos])
	{
		if (pipeline[pos + 1] && pipe(pipeline[pos]->fd) == -1)
			error(minivault, FAILURE, true, "pipe", NULL);
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
