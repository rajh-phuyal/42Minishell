
#include "minishell.h"

// this function adds children to a baobab node
void	connector(t_baobab *node, t_baobab *parent, t_baobab *left, t_baobab *right)
{
	node->left = left;
	node->right = right;
	node->parent = parent;
}

// search tree for a node with the provided token
t_baobab	*search(t_baobab *root, char *token)
{
	if (root)
	{
		if (!ft_strncmp(root->token->token, token, ft_strlen(token)))
			return (root);
		search(root->left, token);
		search(root->right, token);
	}
	return (NULL);
}

// this function creates a babobab node
t_baobab    *create_baobab_node(t_token *token)
{
    t_baobab    *node;

    node = malloc(sizeof(t_baobab));
    if (!node)
        return (NULL);
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return (node);
}