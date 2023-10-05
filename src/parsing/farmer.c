
#include "minishell.h"


// this function tries to build the abstract syntax tree
void    grow_baobab(t_minivault *minivault)
{
    minivault->baobab = create_baobab_node(minivault->tokens);
    print_baobab(minivault->baobab);
    printf("Building the baobab tree...\n");
}