/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:04:34 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/27 15:46:00 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "inputs.h"
# include "executor.h"
# include <sys/stat.h>

// handy macros
# define GET 0
# define PUT 1
# define ERROR -1
# define STDIN 0
# define STDOUT 1

// first few elements of an array
# define FIRST_ELEM 0
# define SECOND_ELEM 1

// exit status related
# define MAXEXTSTATUS 256
# define EXTSTATUSNONNUM 255

typedef enum e_status
{
	SUCCESS=0,
	FAILURE=1,
	CMDNOTFOUND=127,
	SIGINTERRUPT=130,
}	t_status;

// forward declaration for builtins
typedef struct s_word t_word;

// the env list
typedef struct s_envs
{
	char			*key;
	char			*value;
	bool			session;
	bool			internal;
	struct s_envs	*next;
}	t_envs;

// the minieverything
typedef struct s_minivault
{
	char		**input;
	char		**path;
	char		**env_list;
	t_envs		*envs;
	t_baobab	*baobab;
	t_token		*tokens;
}	t_minivault;

// minishell
int			init_minivault(t_minivault *minivault, char **envs);

// input functions
char		*readaline(void);
void		close_readline(void);
void		handle_input(t_minivault *minivault, char *input);

// error handeler
void    	panic_attack(t_minivault *minivault);
void    	error(t_minivault *minivault, t_status status, int prompt, ...);

// environment functions
char		**envsort(t_envs *envs);
char		*get_env(t_minivault *minivault, char *key);
void		unset_env(t_minivault *minivault, char *key);
t_envs  	*get_env_node(t_minivault *minivault, char *key);
void		set_env(t_minivault *minivault, char *key, char *value, int identifier);
void   		add_env_node(t_minivault *minivault, char *key, char *value, int identifier);

// builtin functions
void    	_env(t_minivault *minivault);
void		_pwd(t_minivault *minivault);
void		_cd(t_minivault *minivault, t_word *args);
void		_echo(t_minivault *minivault, t_word *args);
void    	_unset(t_minivault *minivault, t_word *args);
void		_export(t_minivault *minivault, t_word *args);
void    	_exit_vault(t_minivault *minivault, t_word *args);


// debug functions
void		call_debug(t_minivault *minivault);
void		print_argv(int argc, char **argv);
void		print_envs(t_envs *envs);
void		print_vector(char **vector);
void		print_tokens(t_token *head);
void		print_baobab(t_baobab *root, int indent_level);

// the liberator
void		liberate_envs(t_envs *head);
void		liberate_words(t_word *head);
void		liberate_redir(t_redir *head);
void		liberate_vector(char **vector);
void		liberate_tokens(t_token *head);
void		liberate_baobab(t_baobab *head);
void		cycle_reset(t_minivault *minishell);
void		liberation(t_minivault *minivault);

// utils


#endif