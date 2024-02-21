/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:14 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 01:00:48 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_command(t_minivault	*minivault, \
		t_command *command, int in, int out)
{
	int	_stat;

	_stat = -1;
	set_signals(SIG_STATE_BUILTIN);
	out = out;
	if (command->status == 0)
	{
		if (!ft_strncmp(command->words->word, "echo", 5))
			_echo(minivault, command->words->next, out);
		else if (!ft_strncmp(command->words->word, "cd", 3))
			_stat = _cd(minivault, command->words->next);
		else if (!ft_strncmp(command->words->word, "pwd", 4))
			_pwd(minivault, out);
		else if (!ft_strncmp(command->words->word, "export", 7))
			_export(minivault, command->words->next, out);
		else if (!ft_strncmp(command->words->word, "unset", 6))
			_unset(minivault, command->words->next);
		else if (!ft_strncmp(command->words->word, "env", 4))
			_env(minivault, out);
		else if (!ft_strncmp(command->words->word, "exit", 5))
			return (_exit_vault(minivault, command->words->next, out));
		if (_stat >= 0)
			set_env(minivault, PREVEXITSTAT, ft_itoa(_stat), (1 << 1));
	}
	close_pipes(in, out);
}
