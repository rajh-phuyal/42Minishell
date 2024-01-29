/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:19:15 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:40:21 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_builtin(char **builtin_list, char *cmd)
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

void	execute_command(t_minivault *minivault, t_command *command, int pos)
{
	if (command->words)
	{
		if (is_cmd_builtin((char *[]){"echo", "cd", "pwd", "export", \
		"unset", "env", "exit", NULL}, command->words->word))
			builtin_command(minivault, command, pos);
		else
			system_command(minivault, command, pos);
	}
}

void	executor(t_minivault *minivault, t_command **pipeline)
{
	int	pos;

	pos = -1;
	// deal with it
	if (!pipeline)
		return ;
	while (pipeline[++pos])
		execute_command(minivault, pipeline[pos], pos);
}
