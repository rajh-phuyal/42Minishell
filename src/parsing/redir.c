/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:49 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/06 21:02:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_heredoc(t_minivault *minivault, \
			t_command *command, t_token *token)
{
	int	doc_fd;

	if (!(token->next))
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token `newline'", NULL);
		return (-1);
	}
	doc_fd = heredoc(minivault, command, (t_heredoc){{-1, -1}, \
			!(token->next->type == QUOTED), token->next->content}, -1);
	return (doc_fd);
}

static t_operation	find_redirection_type(t_token *token)
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

static void	add_redir_back(t_redir **redir, t_redir *token)
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

static t_redir	*create_redirection_node(t_minivault *minivault, \
		t_command *command, t_token *token, t_token *next)
{
	t_redir	*redir;

	if (!token || !next || !next->content)
	{
		error(minivault, FAILURE, true, \
		"syntax error near unexpected token `newline'", NULL);
		return (NULL);
	}
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->operator = find_redirection_type(token);
	redir->fd = -1;
	redir->next = NULL;
	redir->word = next->content;
	if (redir->operator == DLESS)
	{
		add_redir_back(&(command->redir_in), redir);
		redir->fd = launch_heredoc(minivault, command, token);
	}
	else
		redir->fd = assign_fd(minivault, command, redir->operator, \
			redir->word);
	return (redir);
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
	else if (redir->operator != DLESS)
		add_redir_back(head_in, redir);
}
