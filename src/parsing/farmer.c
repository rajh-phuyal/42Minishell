
#include "minishell.h"

t_baobab	*create_baobab_node(t_token *token, int node_type)
{
    t_baobab    *node;

    node = malloc(sizeof(t_baobab));
    if (!node)
        return (NULL);
    node->token = token;
	(void) node_type;
	// node->type = node_type;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// this function builds the abstract syntax tree
void	grow_baobab(t_minivault	*minivault)
{
	(void) minivault;
	// minivault->baobab = is_job(minivault->tokens);
}
