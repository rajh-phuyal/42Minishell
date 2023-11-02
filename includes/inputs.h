/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:10 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/11/02 14:38:54 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include <readline/history.h>
# include <readline/readline.h>

typedef enum	e_type
{
	WORD,
	PIP,
	REDIR_IN,
	REDIR_OUT
}				t_type;
// type of tokens in ast
typedef enum e_ast_type
{
	CMD,
	ARG,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	HEREDOC,
	APPEND,
}			t_ast_type;

// some functions can't live without the minvault, so ...
typedef struct s_minivault t_minivault;

// the token list
typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
}	t_token;

// abstract syntax tree
typedef struct s_baobab
{
	int				level;
	t_ast_type		type;
	t_token			*token;
	struct s_baobab	*left;
	struct s_baobab	*right;
	struct s_baobab	*parent;
}	t_baobab;

// input functions
char		*readaline(void);
void		close_readline(void);
void		handle_input(t_minivault *minivault, char *input, char **envs);

// tokenizer
void		tokenizer(t_minivault *minivault, int seq);
void    	print_tokens(t_token *head);
void    	remove_token(t_token *head, t_token *node);

// parser
void    	grow_baobab(t_minivault *minivault);
t_baobab	*search(t_baobab *root, char *token);
t_baobab    *create_baobab_node(t_token *token);
void		connector(t_baobab *node, t_baobab *parent, t_baobab *left, t_baobab *right);

#endif