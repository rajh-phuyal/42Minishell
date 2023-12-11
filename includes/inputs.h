#ifndef INPUTS_H
# define INPUTS_H

# include <readline/history.h>
# include <readline/readline.h>

// TOKEN LIST
typedef enum	e_content_type
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

typedef struct s_word // TODO: havig the node called word and the string word aswell is confusing this could change
{
	char			*word;
	struct s_word	*next;

}					t_word;

typedef	enum e_cmd_pos
{
	SINGLE,
	FIRST,
	MIDDLE,
	LAST
} t_cmd_pos;

typedef struct s_command
{
	t_cmd_pos	pos;
	t_word		*words;
	t_redir		*redir_in_list;
	t_redir		*redir_in;
	t_redir		*redir_out_list;
	t_redir		*redir_out;
	bool		pipe_config[2];
	int			pipe_fd[2];
}				t_command;

typedef struct s_baobab
{
	t_command	**pipeline;
}				t_baobab;

typedef struct s_minivault t_minivault;

// lexing
void		lexer(t_minivault *minivault, char *input);
void		strextract(t_minivault *minivault, char *input);
bool		is_single_quote(char c);
bool		is_double_quote(char c);
void		tokenizer(t_minivault *minivault, int seq);
void		remove_token(t_token *head, t_token *node);
t_token 	*create_new(char *token);
void		add_token(t_minivault *minivault, char *token);

// parser
void    	grow_baobab(t_minivault *minivault);
t_baobab	*search(t_baobab *root, char *token);
// t_token		*get_token(t_token *token, t_type type);
t_baobab	*create_baobab_node(t_token *token, int node_type);
void		connector(t_baobab *node, t_baobab *parent, t_baobab *left, t_baobab *right);
void		remove_quotes(char *str);
void		add_word(t_word **word_list, t_token *token);
void		add_redirection(t_command **command, t_token *token, t_token *next);

#endif