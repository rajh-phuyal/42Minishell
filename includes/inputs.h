/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:10 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/06 18:00:19 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include <readline/history.h>
# include <readline/readline.h>

// type of tokens
enum	t_type
{
	CMD,
	ARG,
	PIPE,
	REDIRECT,
	SEMICOLON
};

// some functions can't live without the minvault, so ...
typedef struct s_minivault t_minivault;

// the token list
typedef struct s_token
{
	char			*token;
	enum t_type		type;
	struct s_token	*next;
}	t_token;

// abstract syntax tree
typedef struct s_baobab
{
	int				level;
	struct s_token	*token;
	struct s_baobab	*left;
	struct s_baobab	*right;
	struct s_baobab	*parent;
}	t_baobab;

// input functions
char		*readaline(void);
void		close_readline(void);
void		handle_input(t_minivault *minivault, char *input);

// tokenizer
void    	print_tokens(t_token *head);
void    	add_token(t_minivault *minivault, char *token, int type);
void    	remove_token(t_token *head, t_token *node);

// parser
void    	grow_baobab(t_minivault *minivault);
t_baobab	*search(t_baobab *root, char *token);
t_baobab    *create_baobab_node(t_token *token);
void		connector(t_baobab *node, t_baobab *parent, t_baobab *left, t_baobab *right);

#endif