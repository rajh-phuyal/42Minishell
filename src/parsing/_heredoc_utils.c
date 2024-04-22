/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:04:07 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:04:08 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit_herdoc(t_minivault *minivault, int status)
{
	liberation(minivault);
	exit(status);
}

void	handle_delimeter(t_minivault *minivault, \
				t_command *command, t_heredoc *doc, char *line)
{
	liberate_command(command);
	clean_heredoc_child(minivault, line, doc->fds, SUCCESS);
}

void	clean_heredoc_child(t_minivault *minivault, \
					char *input, int fds[2], int status)
{
	close(fds[WRITE]);
	set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
	if (input)
		free(input);
	clean_exit_herdoc(minivault, status);
}
