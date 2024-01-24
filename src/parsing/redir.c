#include "minishell.h"

/*
 ? GREAT
 ? open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
 * Open or create a file with read and write access
 * If the file already exists, truncate it to zero length
 * Set file permissions to 0644 (read and write for the owner, read for others)

 ? DGREAT
 ? open(file, O_CREAT | O_RDWR, 0644);
 * Open or create a file with read and write access
 * If the file doesn't exist, create it; if it exists, open it without truncating
 * Set file permissions to 0644 (read and write for the owner, read for others)

 ? LESS
 ? open(file, O_RDONLY);
 * Open the file with only read access
 * If the file doesn't exist, trow an errorr
 ! bash: <filename>: No such file or directory

 ? DLESS
 * heredoc
*/

// TODO: ERROR HANDLING
// TODO: HEREDOC
int	assign_fd(t_operation operator, char *file)
{
	int fd;

	fd = -1;
	if (operator == GREAT)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		return (fd);
		// deal with the
	}
	else if (operator == DGREAT)
	{
		fd = open(file, O_CREAT | O_RDWR, 0644);
		return (fd);
	}
	else if (operator == LESS)
	{
		fd = open(file, O_RDONLY);
		return (fd);
		// ! bash: <file>: No such file or directory
	}
	else if (operator == DLESS)
	{

		// set_signals(SIG_STATE_HD_CHILD) in heredoc process
		// set_signals(SIG_STATE_IGNORE) in main process
		// fd = heredoc
		return (fd);
	}
	return (-1);
}

t_operation	find_redirection_type(t_token *token)
{
	if (token->type == REDIRECTION)
	{
		if (!ft_strncmp(token->content, ">>", 2))
			return (DGREAT);
		else if (!ft_strncmp(token->content, "<<", 2))
			return (DLESS);
		else if (!ft_strncmp(token->content, ">", 1))
			return (GREAT);
		else if (!ft_strncmp(token->content, "<", 1))
			return (LESS);
	}
	return (ERROR);
}

t_redir *create_redirection_node(t_token *token, t_token *next)
{
	t_redir *redir;

	if (!token || !next || !next->content)
		return (NULL);
		//bash: syntax error near unexpected token `newline'
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->operator = find_redirection_type(token);
	if (next->type == QUOTED)
		remove_quotes(next->content);
	redir->word = next->content;
	redir->fd = assign_fd(redir->operator, next->content);
	// if (redir->fd == -1)
		// something is fucked
	redir->next = NULL;
	return (redir);
}

void add_redir_back(t_redir **redir, t_redir *token)
{
    t_redir *current = *redir;

    if (!current)
    {
        *redir = token;
        return;
    }

    while (current->next)
        current = current->next;

    current->next = token;
}


void	add_redirection(t_command **command, t_token *token, t_token *next)
{
	t_redir *redir;
    t_redir **head_in = &(*command)->redir_in;
    t_redir **head_out = &(*command)->redir_out;

	redir = NULL;
	if(token && next)
		redir = create_redirection_node(token, next);
	if (!redir) // something is fucked handle this case // || redir->operator == ERROR
		return ;
	if (redir->operator == DGREAT || redir->operator == GREAT)
		add_redir_back(head_out, redir);
	else
		add_redir_back(head_in, redir);
}
