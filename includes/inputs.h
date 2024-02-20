#ifndef INPUTS_H
# define INPUTS_H

# include <readline/history.h>
# include <readline/readline.h>

# define WRITE 1
# define READ 0
# define DOLLAR '$'
# define SHELLEVEL "SHLVL"
# define PLACEHOLDER "\31"
# define DOUBLEQUOTES "\""

// TOKEN LIST
typedef enum e_content_type
{
	LITERAL,
	QUOTED,
	PIPE,
	REDIRECTION,
}				t_content_type;

typedef struct s_token
{
	char			*content;
	t_content_type	type;
	struct s_token	*next; // used initially to build the list
}	t_token;

// AST
// used to identify the redirection node
typedef enum e_operation
{
	GREAT,
	LESS,
	DGREAT,
	DLESS
}			t_operation;

typedef struct s_redir
{
	t_operation		operator;
	int				fd;
	char			*word;
	struct s_redir	*next;
}					t_redir;

// declaration for expansion
typedef struct s_strexp
{
	char	*pos;
	bool	quoted;
	bool	singleq;
	bool	expandable;
}			t_strexp;

/*
TODO 	havig the node called word and the string
TODO 	word aswell is confusing this could change
*/
typedef struct s_word
{
	char			*word;
	struct s_word	*next;

}					t_word;

typedef struct s_inside
{
	bool	dquotes;
	bool	squotes;
}				t_inside;

typedef enum e_cmd_pos
{
	SINGLE,
	FIRST,
	MIDDLE,
	LAST
}			t_cmd_pos;

typedef struct s_command
{
	pid_t		pid;
	bool		is_builtin;
	t_cmd_pos	pos;
	char		*exec_path;
	t_word		*words;
	t_redir		*redir_in;
	t_redir		*redir_out;
}				t_command;

typedef struct s_baobab
{
	t_command	**pipeline;
	int			pipe_fd[FOPEN_MAX][2];
}				t_baobab;

typedef struct s_minivault	t_minivault;

// lexing
void		toggle_quotes(char input, bool *inside_double_quotes, \
								bool *inside_single_quotes);
bool		is_single_quote(char c);
bool		is_double_quote(char c);
t_token		*create_new(char *token);
bool		lexer(t_minivault *minivault, char *input);
void		tokenizer(t_minivault *minivault);
void		remove_token(t_token *head, t_token *node);
void		add_token(t_minivault *minivault, char *token);
char		*strextract(char *line);
void		strexpand(t_minivault *minivault, char **vector);
char		*remove_token_quotes(char *input);

// expansion utils
char		*get_suffix(char *str);
void		_cleaner(t_strexp *data);
bool		_has_expander(char *str);
bool		_is_heredoc_deli(char *str, char **vector);
void		_put_end_break(char *start, t_strexp *data);
char		*build_or_not_build(char *_built, t_strexp *data);
char		*update_built(char *built, char *value, char curr_char, char *pos);
bool		unpack_var(t_strexp *data, bool quoted, bool singleq, bool expandable);
void		finilize_magic_str(char **v_iter, char *curr, char *_magic, t_strexp *data);

// parser

char		*remove_quotes(char *str, char flag);

void		grow_baobab(t_minivault *minivault);
t_baobab	*search(t_baobab *root, char *token);
void		add_word(t_word **word_list, t_token *token);
int			count_tokens(t_content_type token_type, t_token *tokens);
void		connector(t_baobab *node, t_baobab *parent, \
			t_baobab *left, t_baobab *right);
void		add_redirection(t_minivault *minivault, \
			t_command **command, t_token *token, t_token *next);

char		*get_exec_path(t_minivault *minivault, char *exec_name);

#endif