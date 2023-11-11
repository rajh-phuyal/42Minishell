/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:10 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/11/11 16:18:33 by rajphuyal        ###   ########.fr       */
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
	LESS,
	GREAT
}				t_type;

// type of tokens in ast
// typedef enum e_ast_type
// {
// 	CMD,
// 	ARG,
// 	PIPE,
// 	LESS,
// 	GREAT,
// 	DLESS,
// 	DGREAT,
// }			t_ast_type;

// some functions can't live without the minvault, so ...
typedef struct s_minivault t_minivault;

// the token list
typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
}	t_token;

// abstract syntax tree
typedef struct s_baobab
{
	int				level;
	// t_ast_type		type;
	t_token			*token;
	struct s_baobab	*left;
	struct s_baobab	*right;
	struct s_baobab	*parent;
}	t_baobab;

// lexing
void		lexer(t_minivault *minivault, char *input);
void		strextract(t_minivault *minivault, char *input);
bool		is_single_quote(char c);
bool		is_double_quote(char c);
void		tokenizer(t_minivault *minivault, int seq);
void		remove_token(t_token *head, t_token *node);

// parser
void    	grow_baobab(t_minivault *minivault);
t_baobab	*search(t_baobab *root, char *token);
t_token		*get_token(t_token *token, t_type type);
t_baobab	*create_baobab_node(t_token *token, int node_type);
void		connector(t_baobab *node, t_baobab *parent, t_baobab *left, t_baobab *right);

#endif