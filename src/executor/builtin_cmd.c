/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:14 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 21:30:38 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_command(t_minivault	*minivault, \
		t_command *command, int in, int out)
{
	int	_stat;

	_stat = SUCCESS;
	(void)in;
	set_signals(SIG_STATE_BUILTIN);
	if (command->status == 0)
	{
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
		{
			close_pipes(in, out);
			close_pipes(command->fd[0], command->fd[1]);
			return (_exit_vault(minivault, command->words->next, out));
		}
		set_env(minivault, PREVEXITSTAT, ft_itoa(_stat), (1 << 1));
		if (minivault->cmd_count > 1)
		{
			close(command->fd[0]);
			close_pipes(in, out);
			liberate_vector(minivault->input);
			liberation(minivault);
			exit(_stat);
		}
	}
}
