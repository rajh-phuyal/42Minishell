/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:05:14 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/01 16:15:13 by rajphuyal        ###   ########.fr       */
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
        printf("TOKEN: %s\n", head->token);
        head = head->next;
    }
}
