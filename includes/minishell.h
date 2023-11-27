#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "inputs.h"
# include "executor.h"
// # include "macros.h"

// handy macros
# define GET 0
# define PUT 1
# define ERROR -1


// Types of errors minishell can throw, add more types of errors here
/*
	CNF: COMMAND DOES NOT EXIST,
	FNF: FILE DOES NOT EXIST,
	FDNF: FILE OR DIRECTORY DOES NOT EXIST
	S_EXIT: SIMPLY EXIT THE PROGRAM,
	NOTADIR: THE PATH IS NOT A DIRECTORY,
	PDENIED: PERMISSION DENIED,
*/
typedef enum	e_error_type
{
	EXIT,
	CMDNF,
	SYNTAX,
	FINENF,
	NOTADIR,
	PDENIED,
	FILEORDIRNF,
}	t_error_type;

// this has the data for errors
typedef struct s_error
{
	int		fd;
	bool	exit;
	int		status;
	char	*message;
	char	*err_token;
}	t_error;

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
	t_error		*error;
}	t_minivault;

t_minivault	*minishell(void);

// minishell
int			init_minivault(t_minivault *minivault, char **envs);

// input functions
char		*readaline(void);
void		close_readline(void);
void		handle_input(t_minivault *minivault, char *input, char **envs);

// error handeler
void    	error(t_error_type type, t_minivault *minivault, char *token, int status);

// environment functions
void 		envsort(t_envs *envs);
char		*get_env(t_minivault *minivault, char *key);
void		unset_env(t_minivault *minivault, char *key);
t_envs		*add_env_node(t_envs *envs, char *key, char *value);
void		set_env(t_minivault *minivault, char *key, char *value);

// debug functions
void		call_debug(t_minivault *minivault);
void		print_argv(int argc, char **argv);
void		print_envs(t_envs *envs);
void		print_vector(char **vector);
void		print_tokens(t_token *head);
void		print_baobab(t_baobab *root, int indent_level);

// the liberator
void		liberation(t_minivault *minivault);
void		liberate_envs(t_envs *head);
void		liberate_vector(char **vector);
void		liberate_tokens(t_token *head);
void		liberate_baobab(t_baobab *head);

// utils
void    	clean_exit(t_minivault *minivault, int status);
#endif