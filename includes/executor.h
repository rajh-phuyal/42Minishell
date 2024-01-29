/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:21:03 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:27:08 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_herdoc
{
	int			fds[2];
	bool		expandable;
	char		*delimiter;
}				t_heredoc;

t_redir		*get_last_token(t_redir *head);
void		executor(t_minivault *minivault, t_command **pipeline);
void		config_io(t_minivault	*minivault, t_command *command, int pos);
int			config_io_builtin(t_minivault *minivault, \
			t_command *command, int pos);
char		*handle_path(t_minivault *minivault, char *cmd);
void		system_command(t_minivault *minivault, t_command *command, int pos);
void		close_pipes(t_minivault	*minivault, t_command *command, int pos);
void		builtin_command(t_minivault	*minivault, \
			t_command *command, int pos);
int			heredoc(t_minivault *minivault, t_command *command, t_heredoc doc);

#endif