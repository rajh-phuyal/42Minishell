#include "minishell.h"
int	g_signal_status;

void    clean_exit_herdoc(t_minivault *minivault, int status)
{
    liberation(minivault);
    exit(status);
}

void	clean_heredoc_child(t_minivault *minivault, char *input, int fds[2], int status)
{
	close(fds[WRITE]);
    set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
    if (input)
		free(input);
	clean_exit_herdoc(minivault, status);
}

static void	_check_sig_eof(t_minivault *minivault, t_heredoc *doc, char *input)
{
    char    *cycle;

	if (g_signal_status == SIGNAL_EXIT_HD)
        clean_heredoc_child(minivault, input, doc->fds, SUCCESS);
	if (!input)
	{
        cycle = ft_itoa(minivault->cycles);
        error(minivault, FAILURE, true, "warning: ",
            "here-document at line ", cycle, " delimited by end-of-file (wanted `", doc->delimiter, "')", NULL);
        free(cycle);
		clean_heredoc_child(minivault, input, doc->fds, SUCCESS);
	}
}

int handle_parent(t_minivault *minivault, t_heredoc *doc, int pid)
{
	int	_stat;

	_stat = 0;
	close(doc->fds[WRITE]);
	set_signals(SIG_STATE_IGNORE);
	waitpid(pid, &_stat, 0);
	set_signals(SIG_STATE_HD_CHILD);
	if (_stat != SUCCESS)
	{
		g_signal_status = SIGNAL_EXIT_HD;
        set_env(minivault, "?", ft_itoa(WEXITSTATUS(_stat)), (1 << 1));
		close(doc->fds[READ]);
		return (-1);
	}
	else
		return (doc->fds[READ]);
}

char    *_str_expand(t_minivault *minivault, char *line)
{
    int     i;
    char    **temp;
    char    *_built;
    // char    *freeable;

    i = 0;
    temp = ft_split(line, ' ');
    if (!temp)
        return (line);
    strexpand(minivault, temp);
    print_vector(temp);
    _built = ft_strdup("");
    while (temp && temp[i])
    {
        // freeable = _built;
        _built = ft_strjoin(_built, temp[i]);
        // free(freeable);
        i++;
    }
    // liberate_vector(temp);
    free(temp);
    return (line);
}

void    start_heredoc(t_minivault *minivault, t_heredoc *doc)
{
    char    *line;

	set_signals(SIG_STATE_HD_CHILD);
    close(doc->fds[WRITE]);
    while (true)
    {
        line = readline("doc> ");
        _check_sig_eof(minivault, doc, line);
        if (line && line[0] != '\0')
        {
            if (ft_strncmp(line, doc->delimiter, ft_strlen(doc->delimiter)) == 0)
            {
                clean_heredoc_child(minivault, line, doc->fds, SUCCESS);
                return ;
            }
            if (doc->expandable && line)
				line = _str_expand(minivault, line); // this needs to be hammered
            ft_putendl_fd(line, doc->fds[WRITE]);
        }
        else
            ft_putendl_fd("", doc->fds[WRITE]);
        // if (line)
        //     free(line);
    }
}

int heredoc(t_minivault *minivault, t_heredoc doc)
{
    pid_t   pid;

    if (pipe(doc.fds) < 0)
    {
        clean_exit_herdoc(minivault, FAILURE);
        return (-1);
    }
    pid = fork();
    if (pid == -1)
    {
        clean_exit_herdoc(minivault, FAILURE);
        return (-1);
    }
    if (pid == 0)
        start_heredoc(minivault, &doc);
    return (handle_parent(minivault, &doc, pid));
}
