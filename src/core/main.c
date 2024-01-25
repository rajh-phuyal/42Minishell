
#include "minishell.h"

/* call the debug functions to check the state of the program variables*/
void	call_debug(t_minivault *minivault)
{
	printf("\n---------VECTOR-------\n");
	print_vector(minivault->input);
	// printf("\n----------ENV---------\n");
	// print_envs(minivault->envs);
	printf("\n----------LIST--------\n");
	print_tokens(minivault->tokens);
	// printf("\n----------TREE--------\n");
	// print_baobab(minivault->baobab, 0);
}


void	handle_input_file(char **argv)
{
	(void)argv;
}

int	main(int argc, char **argv, char **envs)
{
	t_minivault	minivault;

	set_signals(SIG_STATE_MAIN);
	init_minivault(&minivault, envs);
	if (argc != 1)
		handle_input_file(argv);
	while (true)
		handle_input(&minivault, readaline());
	close_readline();
	liberation(&minivault);
	return (0);
}

// Dear programmer:
// When I wrote this code, only god and
// I knew how it worked.
// Now, only god knows it!
//
// Therefore, if you are trying to optimize it, and it fails (most surely),
// please increase this counter as a warning for the next person:
//
// total_hours_wasted_here = 256