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

int	launch_heredoc(t_minivault *minivault, t_command *command, t_token *token)
{
	int doc_fd;

	if (!(token->next))
	{
		error(minivault, FAILURE, true, "syntax error near unexpected token `newline'", NULL);
		return (-1);
	}
	doc_fd = heredoc(minivault, command, (t_heredoc){{-1, -1}, !(token->next->type == QUOTED), token->next->content});
	return (doc_fd);
}

// TODO: ERROR HANDLING
// TODO: HEREDOC
int	assign_fd(t_minivault *minivault, t_command *command, t_operation operator, char *file, t_token *token)
{
	if (operator == GREAT)
		return (open(file, O_CREAT | O_RDWR | O_TRUNC, 0644));
	else if (operator == DGREAT)
		return (open(file, O_CREAT | O_RDWR | O_APPEND, 0644));
	else if (operator == LESS)
		return (open(file, O_RDONLY));
	// ! bash: <file>: No such file or directory
	else if (operator == DLESS)
		return (launch_heredoc(minivault, command, token));
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

t_redir *create_redirection_node(t_minivault *minivault, t_command *command, t_token *token, t_token *next)
{
	t_redir *temp;
	t_redir *redir;

	if (!token || !next || !next->content)
	{
		error(minivault, FAILURE, true, "syntax error near unexpected token `newline'", NULL);
		return (NULL);
	}
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->operator = find_redirection_type(token);
	redir->fd = -1;
	temp = command->redir_in;
	command->redir_in = redir;
	redir->next = NULL;
	if (next->type == QUOTED)
		remove_quotes(next->content);
	redir->word = next->content;
	redir->fd = assign_fd(minivault, command, redir->operator, next->content, token);
	command->redir_in = temp;
	// if (redir->fd == -1)
		// something is fucked
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


void	add_redirection(t_minivault *minivault, t_command **command, t_token *token, t_token *next)
{
	t_redir *redir;
    t_redir **head_in = &(*command)->redir_in;
    t_redir **head_out = &(*command)->redir_out;

	redir = NULL;
	if(token && next)
		redir = create_redirection_node(minivault, *command, token, next);
	if (!redir) // something is fucked handle this case // || redir->operator == ERROR
		return ;
	if (redir->operator == DGREAT || redir->operator == GREAT)
		add_redir_back(head_out, redir);
	else
		add_redir_back(head_in, redir);
}
