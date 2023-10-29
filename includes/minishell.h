/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:11:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/29 15:00:05 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "inputs.h"
# include "executor.h"
// # include "macros.h"

// handy macros
# define GET 0
# define PUT 1

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

// environment functions
void 		envsort(t_envs *envs);
char		*get_env(t_minivault *minivault, char *key);
void		unset_env(t_minivault *minivault, char *key);
t_envs		*add_env_node(t_envs *envs, char *key, char *value);
void		set_env(t_minivault *minivault, char *key, char *value);

// parsing gate
void		lexer(t_minivault *minivault, char *input);
void		strextract(t_minivault *minivault, char *input);
bool		is_single_quote(char c);
bool		is_double_quote(char c);

// debug functions
void		print_envs(t_envs *envs);
void		print_baobab(t_baobab *root);
void		print_argv(int argc, char **argv);
void		print_vector(char **vector);

// the liberator
void		liberate_vector(char **vector);
void    	liberation(t_minivault *minivault);

#endif