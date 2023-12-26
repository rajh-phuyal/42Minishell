#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>

t_redir *get_last_token(t_redir *head);
void	executor(t_minivault *minivault, t_command **pipeline);
void	config_io(t_minivault	*minivault, t_command *command, int pos);
void	system_command(t_minivault *minivault, t_command *command, int pos);
void	close_pipes(t_minivault	*minivault, t_command *command, int pos);
void	builtin_command(t_minivault	*minivault, t_command *command, int pos);


#endif