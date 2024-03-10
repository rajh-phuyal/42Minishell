/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:14 by jalves-c          #+#    #+#             */
/*   Updated: 2024/03/10 17:34:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	close_cmd_pipes(t_command *command, int pipein, int pipeout)
{
	close_pipes(pipein, pipeout);
	close_pipes(command->fd[0], command->fd[1]);
}

static	void	close_and_free(t_minivault *minivault, \
	t_command *command, int in, int out)
{
	close(command->fd[0]);
	close_pipes(in, out);
	liberate_vector(minivault->input);
	liberation(minivault);
}

static	void	exec_builtin(t_minivault *minivault, \
	t_command *command, int in, int out)
{
	int	_stat;

	_stat = SUCCESS;
	if (!ft_strncmp(command->words->word, "echo", 5))
		_echo(minivault, command->words->next, out);
	else if (!ft_strncmp(command->words->word, "cd", 3))
		_stat = _cd(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "pwd", 4))
		_pwd(minivault, out);
	else if (!ft_strncmp(command->words->word, "export", 7))
		_stat = _export(minivault, command->words->next, out);
	else if (!ft_strncmp(command->words->word, "unset", 6))
		_unset(minivault, command->words->next);
	else if (!ft_strncmp(command->words->word, "env", 4))
		_env(minivault, out);
	else if (!ft_strncmp(command->words->word, "exit", 5))
		return (close_cmd_pipes(command, in, out), \
		_exit_vault(minivault, command->words->next, out));
	set_env(minivault, PREVEXITSTAT, ft_itoa(_stat), (1 << 1));
	if (minivault->cmd_count > 1)
	{
		close_and_free(minivault, command, in, out);
		exit(_stat);
	}
}

void	builtin_command(t_minivault	*minivault, \
		t_command *command, int in, int out)
{
	(void)in;
	set_signals(SIG_STATE_BUILTIN);
	if (command->status == 0)
		exec_builtin(minivault, command, in, out);
}
