#include "minishell.h"

int	launch_heredoc(t_minivault *minivault, t_command *command, t_token *token)
{
	int	doc_fd;

	if (!(token->next))
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token `newline'", NULL);
		return (-1);
	}
	doc_fd = heredoc(minivault, command, (t_heredoc){{-1, -1}, \
		!(token->next->type == QUOTED), token->next->content});
	return (doc_fd);
}

t_operation	find_redirection_type(t_token *token)
{
	if (token->type == REDIRECTION)
	{
		if (!ft_strncmp(token->content, ">>", 3))
			return (DGREAT);
		else if (!ft_strncmp(token->content, "<<", 3))
			return (DLESS);
		else if (!ft_strncmp(token->content, ">", 2))
			return (GREAT);
		else if (!ft_strncmp(token->content, "<", 2))
			return (LESS);
	}
	return (ERROR);
}

t_redir	*create_redirection_node(t_minivault *minivault, \
		t_command *command, t_token *token, t_token *next)
{
	t_redir	*temp;
	t_redir	*redir;

	if (!token || !next || !next->content)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token `newline'", NULL);
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
	redir->word = next->content;
	if (redir->operator == DLESS)
		redir->fd = launch_heredoc(minivault, command, token);
	else
		redir->fd = assign_fd(minivault, redir->operator, \
			redir->word);
	command->redir_in = temp;
	return (redir);
}

void	add_redir_back(t_redir **redir, t_redir *token)
{
	t_redir	*current;

	current = *redir;
	if (!current)
	{
		*redir = token;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = token;
}

void	add_redirection(t_minivault *minivault, \
		t_command **command, t_token *token, t_token *next)
{
	t_redir	*redir;
	t_redir	**head_in;
	t_redir	**head_out;

	head_in = &(*command)->redir_in;
	head_out = &(*command)->redir_out;
	redir = NULL;
	if (token && next)
		redir = create_redirection_node(minivault, *command, token, next);
	if (!redir)
		return ;
	if (redir->operator == DGREAT || redir->operator == GREAT)
		add_redir_back(head_out, redir);
	else
		add_redir_back(head_in, redir);
}
