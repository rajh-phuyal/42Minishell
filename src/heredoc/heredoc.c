#include "minishell.h"

void    clean_exit(t_minivault *minivault, int status)
{
    (void)minivault;
    (void)status;
    return ;
}

void	clean_heredoc_child(t_minivault *minivault, char *input, int fds[2], int status)
{
	close(fds[WRITE]);
    set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
    if (input)
		free(input);
	clean_exit(minivault, status);
}

int handle_parent(t_minivault *minivault, t_heredoc *doc, int pid)
{
	int	_stat;

	_stat = 0;
	close(doc->fds[WRITE]);
    // TODO: config signal handler, to ignore all signals
	set_signals(SIG_STATE_IGNORE);
	waitpid(pid, &_stat, 0);
    // TODO: config signal handler, to handle child signals
	set_signals(SIG_STATE_HD_CHILD);
	if (_stat != EXIT_SUCCESS)
	{
		// g_signal_status = SIGINTERRUPT; // for now asuming siginterupt
        set_env(minivault, "?", ft_itoa(WEXITSTATUS(_stat)), (1 << 1));
		close(doc->fds[READ]);
		return (-1);
	}
	else
		return (doc->fds[READ]);
}

char    *_strexpand(t_minivault *minivault, char *line)
{
    (void)minivault;
    return (line);
}

void    start_heredoc(t_minivault *minivault, t_heredoc *doc)
{
    char    *line;

    // TODO: handel signals and fds
	set_signals(SIG_STATE_HD_CHILD);
    close(doc->fds[WRITE]);
    while (true)
    {
        line = readline("doc> ");
        // TODO: handel signals before continuing
		// ? : What signal
        if (line && line[0] != '\0')
        {
            if (!ft_strncmp(line, doc->delimiter, ft_strlen(doc->delimiter)))
            {
                clean_heredoc_child(minivault, line, doc->fds, EXIT_SUCCESS);
                return ;
            }
            if (doc->expandable && line)
				line = _strexpand(minivault, line); // this needs to be hammered
            ft_putendl_fd(line, doc->fds[WRITE]);
        }
        else
            ft_putendl_fd("", doc->fds[WRITE]);
        if (line)
            free(line);
    }
}

int heredoc(t_minivault *minivault, t_heredoc doc)
{
    pid_t   pid;

    if (pipe(doc.fds) < 0)
    {
        clean_exit(minivault, EXIT_FAILURE);
        return (-1);
    }
    pid = fork();
    if (pid == -1)
    {
        clean_exit(minivault, EXIT_FAILURE);
        return (-1);
    }
    if (pid == 0)
        start_heredoc(minivault, &doc);
    return (handle_parent(minivault, &doc, pid));
}
