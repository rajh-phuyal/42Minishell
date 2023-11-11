
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
		if (!ft_strncmp(root->token->content, token, ft_strlen(token)))
			return (root);
		search(root->left, token);
		search(root->right, token);
	}
	return (NULL);
}

t_token	*get_token(t_token *token, t_type type)
{
	while (token)
	{
		if (token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}