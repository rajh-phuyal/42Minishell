#include "minishell.h"

// closes the readline library
void	close_readline(void)
{
	clear_history();
}

char	*readaline(void)
{
	char	*line;

	line = readline("minibaiters $ ");
	if (line && *line)
		add_history(line);
	return (line);
}

void	handle_input(t_minivault *minivault, char *input)
{
	set_signals(SIG_STATE_MAIN);
	if (!input)
		_exit_vault(minivault, NULL);
	minivault->line = input;
	if (lexer(minivault, input))
	{
		grow_baobab(minivault);
		executor(minivault, minivault->baobab->pipeline);
		call_debug(minivault);
	}
	cycle_reset(minivault);
}
