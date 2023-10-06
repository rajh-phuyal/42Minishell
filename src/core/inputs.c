
#include "minishell.h"

// initializes the readline library
int	init_readline(void)
{
	rl_initialize();
	rl_bind_key('\t', rl_complete);
	return (1);
}

// closes the readline library
void	close_readline(void)
{
	clear_history();
}

// just reads a line form the terminal
char	*readaline(void)
{
	char	*line;

	line = readline("minibaiters $ ");
	if (line && *line)
		add_history(line); // doing it for later user
	return (line);
}

t_readlinedata *readlinedata(void)
{
	static t_readlinedata readlinedata;

	return (&readlinedata);
}

void	handle_input(t_minivault *minivault, char *input)
{
	readlinedata()->line = input;
	lexer(minivault, input);
}
