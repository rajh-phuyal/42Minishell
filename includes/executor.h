/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:30:41 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 00:40:03 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

# ifdef __darwin__
#  include <limits.h>
# endif

# ifdef __linux__
#  include <linux/limits.h>
# endif

# include <unistd.h>
# include <sys/wait.h>

// ? heredoc or herdoc
typedef struct s_herdoc
{
	int		fds[2];
	bool	expandable;
	char	*delimiter;
}			t_heredoc;

// t_redir	*get_last_token(t_redir *head);
void	executor(t_minivault *minivault, t_command **pipeline);
// void	config_io(t_minivault	*minivault, t_command *command, int pos);
// void	config_middle_outfile(t_minivault *minivault, int pos);
// int		config_io_builtin(t_minivault *minivault, t_command *command, int pos);
void	system_command(t_minivault *minivault, t_command *command, int in, int out);
// void	close_pipes(t_minivault	*minivault, t_command *command, int pos);
void	close_pipes(int in, int out);
void	builtin_command(t_minivault	*minivault, t_command *command, int in, int out);
int		heredoc(t_minivault *minivault, t_command *command, t_heredoc doc);
void	clean_exit_herdoc(t_minivault *minivault, int status);
void	handel_delimeter(t_minivault *minivault, \
		t_command *command, t_heredoc *doc, char *line);
void	clean_heredoc_child(t_minivault *minivault, \
		char *input, int fds[2], int status);

bool	check_redirs(t_redir *head);

#endif