
#include "minishell.h"

bool	is_pipeline(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
			return (true);
		current = current->next;
	}
	return (false);
}

int		find_redirection_type(t_token *token)
{
	if (token->type != REDIRECTION)
		return (-1);// deu merda somewhere
	if (!ft_strncmp(token->content, ">>", 2))
		return (DGREAT);
	else if (!ft_strncmp(token->content, "<<", 2))
		return (DLESS);
	else if (!ft_strncmp(token->content, ">", 1))
		return (GREAT);
	else if (!ft_strncmp(token->content, "<", 1))
		return (LESS);
	// deu merda
	return (-1);
}

t_redir	*redirection(t_token *head, t_token *token)
{
	t_redir	*redir;

	redir = NULL;
	if (token->next == NULL)
	{
		// minibaiter:: syntax error near unexpected token `newline'
		return (NULL); // wtf?
	}
	else if (token->type == REDIRECTION && token->next->type == REDIRECTION)
	{
		// minibaiter: syntax error near unexpected token `>'
		return (NULL); // wtf?
	}
	else if (token->type == REDIRECTION && token->next->type != REDIRECTION && token->next->type != PIPE)
	{
		redir->operator = find_redirection_type(token);
		redir->word = ft_strdup(token->next->content); // dont know if should make a copy or just use the old pointer
		remove_token(head, token->next);
		remove_token(head, token);
	}
	printf ("hello\n");
	return (redir);
}

int		count_redirections(t_token *tokens)
{
	t_token	*current;
	int i;

	current = tokens;
	i = 0;
	while (current)
	{
		if (current->type == REDIRECTION)
			i++;
		current = current->next;
	}
	return (i);
}

void	command(t_baobab *baobab, t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	baobab = (t_baobab *)malloc(sizeof(t_baobab));
	if (!baobab)
	{
		printf ("Merda na alocacao do baobab\n");
		return ;
	}
	baobab->u_root.command = (t_command *)malloc(sizeof(t_command));
	if (baobab->u_root.command == NULL)
	{
		printf ("Merda na alocacao dos command\n");
		return ;
	}
	baobab->u_root.command->redirects = (t_redir **)malloc(sizeof(t_redir) * count_redirections(tokens));
	if (baobab->u_root.command->redirects == NULL)
	{
		printf ("Merda na alocacao dos redirects\n");
		return ;
	}
	while (current)
	{
		if (current->type == REDIRECTION)
			baobab->u_root.command->redirects[i++] = redirection(tokens, current);
		current = current->next;
	}	
}

// this function builds the abstract syntax tree
void	grow_baobab(t_minivault	*minivault)
{
	// if (is_pipeline(minivault->tokens))
	// 	pipeline(minivault->tokens);
	// else
		command(minivault->baobab, minivault->tokens);
}
