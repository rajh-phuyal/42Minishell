/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:05:14 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/02 19:01:18 by rajphuyal        ###   ########.fr       */
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

void	print_envs(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
}

void    print_tokens(t_token *head)
{
    while (head)
    {
        printf("TOKEN: %s | TYPE: %d\n", head->token, head->type);
        head = head->next;
    }
}

void	print_baobab(t_baobab *root)
{
	if (root)
	{
		printf("TREE NODE : %s\n", root->token->token);
	}
}