/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:05:20 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:05:21 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_check_sig_eof(t_minivault *minivault, t_command *command, \
		t_heredoc *doc, char *input)
{
	char	*cycle;

	if (g_signal_status == SIGNAL_EXIT_HD)
	{
		liberate_command(command);
		clean_heredoc_child(minivault, input, doc->fds, FAILURE);
	}
	if (!input)
	{
		cycle = ft_itoa(minivault->cycles);
		error(minivault, FAILURE, true, "warning: ", \
			"here-document at line ", cycle, \
			" delimited by end-of-file (wanted `", doc->delimiter, "')", NULL);
		free(cycle);
		liberate_command(command);
		clean_heredoc_child(minivault, input, doc->fds, SUCCESS);
	}
}

static int	handle_parent(t_minivault *minivault, t_heredoc *doc, int pid)
{
	int	_stat;

	set_signals(SIG_STATE_IGNORE);
	_stat = 0;
	close(doc->fds[WRITE]);
	waitpid(pid, &_stat, 0);
	if (_stat != SUCCESS)
	{
		g_signal_status = SIGINTERRUPT;
		minivault->is_exec = 0;
		set_env(minivault, "?", ft_itoa(WEXITSTATUS(_stat)), (1 << 1));
		close(doc->fds[READ]);
		return (-1);
	}
	else
		return (doc->fds[READ]);
}

/* fake a 2D array that the expansion needs, \31 doesn't exist on the str */
static char	*_str_expand(t_minivault *minivault, char *line)
{
	char	**temp;
	char	*_built;

	temp = ft_split(line, '\31');
	if (!temp)
		return (line);
	strexpand(minivault, temp);
	_built = temp[FIRST_ELEM];
	free(temp);
	return (_built);
}

static void	start_heredoc(t_minivault *minivault, \
				t_command *command, t_heredoc *doc)
{
	char	*line;

	set_signals(SIG_STATE_HD_CHILD);
	close(doc->fds[READ]);
	while (true)
	{
		line = readline("doc> ");
		_check_sig_eof(minivault, command, doc, line);
		if (line && line[FIRST_ELEM] != '\0')
		{
			if (ft_strncmp(line, doc->delimiter, \
					ft_strlen(doc->delimiter) + 1) == 0)
				return (handle_delimeter(minivault, command, doc, line));
			if (doc->expandable && line)
				line = _str_expand(minivault, line);
			ft_putendl_fd(line, doc->fds[WRITE]);
		}
		else if (line && !(*doc->delimiter))
			return (handle_delimeter(minivault, command, doc, line));
		else
			ft_putendl_fd("", doc->fds[WRITE]);
		if (line)
			free(line);
	}
}

int	heredoc(t_minivault *minivault, t_command *command, t_heredoc doc, int fd)
{
	pid_t	pid;

	if (minivault->is_exec == 0)
		return (-1);
	if (pipe(doc.fds) < 0)
	{
		liberate_command(command);
		clean_exit_herdoc(minivault, FAILURE);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		liberate_command(command);
		clean_exit_herdoc(minivault, FAILURE);
		return (-1);
	}
	if (pid == 0)
		start_heredoc(minivault, command, &doc);
	fd = handle_parent(minivault, &doc, pid);
	if (fd == -1)
		command->status = 1;
	close_pipes(command->infile_fd, 1);
	command->infile_fd = fd;
	return (fd);
}
