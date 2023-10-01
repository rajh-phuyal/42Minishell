/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:11:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/30 21:40:33 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "inputs.h"

// the minieverything
typedef struct s_minishell
{
	char		**envp;
	char		*input;
	t_token		*token;
	t_baobab	*tree;
}	t_minishell;

t_minishell	*minishell(void);

// minishell
int			init_minishell(void);

// parsing gate
void		lexer(char *input);

// debug functions
void		print_envs(char **envp);
void		print_argv(int argc, char **argv);

#endif