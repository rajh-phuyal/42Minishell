/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:10 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/02 00:40:34 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include <readline/history.h>
# include <readline/readline.h>

// token types
# define PIPE 1
# define WORD 2
# define REDIRECT 3
# define SEMICOLON 4

// some functions can't live without the minvault, so ...
typedef struct s_minivault t_minivault;

// the token list
typedef struct s_token
{
	int				type;
	int				index;
	char			*token;
	struct s_token	*next;
}	t_token;

// abstract syntax tree
typedef struct s_baobab
{
	struct s_token	*token;
	struct s_baobab	*left;
	struct s_baobab	*right;
}	t_baobab;

// input functions
char	*readaline(void);
int		init_readline(void);
void	close_readline(void);
void	handle_input(t_minivault *minivault, char *input);

// tokenizer
void    print_tokens(t_token *head);
void    add_token(t_minivault *minivault, char *token);
void    remove_token(t_token *head, t_token *node);

// parser
void    build_baobab(t_minivault *minivault);


#endif