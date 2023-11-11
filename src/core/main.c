
#include "minishell.h"

/* call the debug functions to check the state of the program variables*/
void	call_debug(t_minivault *minivault)
{
	printf("\n----------VECTOR--------\n");
	print_vector(minivault->input);
	// print_envs(minivault->envs);
	printf("\n----------LIST--------\n");
	print_tokens(minivault->tokens);
	// printf("\n----------TREE--------\n");
	// print_baobab(minivault->baobab, 0);
}

void	handle_input_file(char **argv)
{
	(void)argv;
	// TODO: Handle the script file input, argv[1] only, ignore the rest
}
int	main(int argc, char **argv, char **envs)
{
	t_minivault	minivault;

	if (argc != 1)
		handle_input_file(argv);
	while (true)
		handle_input(&minivault, readaline(), envs);
	close_readline();
	return (0);
}
