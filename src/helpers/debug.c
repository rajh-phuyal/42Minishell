/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:05:14 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/16 20:39:46 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	printf("argc: %d\n", argc);
	while (i < argc)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
}

void	print_vector(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
	{
		printf("%d: %s\n", i, vector[i]);
		i++;
	}
}

void	print_envs(t_envs *envs)
{
	while (envs)
	{
		printf("[ (key): %s | (value): %s | (internal): %d | (session): %d ]\n",
				envs->key, envs->value, envs->internal, envs->session);
		envs = envs->next;
	}
}

void    print_tokens(t_token *head)
{
    while (head)
    {
        printf("TOKEN: %s | TYPE: %d\n", head->content, head->type);
        head = head->next;
    }
}

/*
// ! stolen from anatollii
void	print_baobab(t_baobab *root, int indent_level)
{
	int		type;
	char	*code;
	int		distance;
	if (root == NULL)
		return ;
	distance = 7;
	indent_level += distance;
	print_baobab(root->right, indent_level);
	type = root->type;
	if (type == ARG)
		code = ft_strdup("arg");
	else if (type == CMD)
		code = ft_strdup("cmd");
	else if (type == PIPE)
		code = ft_strdup("|");
	else if (type == APPEND)
		code = ft_strdup(">>");
	else if (type == HEREDOC)
		code = ft_strdup("<<");
	else if (type == REDIRECTION_IN)
		code = ft_strdup("<");
	else if (type == REDIRECTION_OUT)
		code = ft_strdup(">");
	printf("\n");
	for (int i = distance; i < indent_level; i++)
		printf(" ");
	if (root->token->content)
		printf("[%d] (%s)\n", type, root->token->content);
	else
		printf("[%s]\n", code);
	free(code);
	print_baobab(root->left, indent_level);
}
*/
