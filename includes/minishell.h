/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:11:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/14 17:55:46 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "inputs.h"
# include "executor.h"
// # include "macros.h"

// the env list
typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}	t_envs;

// the minieverything
typedef struct s_minivault
{
	char		**input;
	t_envs		*envs;
	t_baobab	*baobab;
	t_token		*tokens;
}	t_minivault;

t_minivault	*minishell(void);

// minishell
int			init_minivault(t_minivault *minivault, char **envs);

// parsing gate
void		lexer(t_minivault *minivault, char *input);
void		strextract(t_minivault *minivault, char *input);

// debug functions
void		print_envs(char **envp);
void		print_baobab(t_baobab *root);
void		print_argv(int argc, char **argv);

// the liberator
void    	liberation(t_minivault *minivault);

#endif