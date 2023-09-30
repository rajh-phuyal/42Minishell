/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:10 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/30 21:28:28 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include <readline/readline.h>
# include <readline/history.h>

// the token list
typedef struct s_token
{
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

char	*readaline(void);
int		init_readline(void);
void	close_readline(void);
void	handle_input(char *input);

#endif