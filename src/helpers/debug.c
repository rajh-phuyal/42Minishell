/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:57:50 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 21:57:55 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_argv(int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	printf("argc: %d\n", argc);
// 	while (i < argc)
// 	{
// 		printf("argv[%d]: %s\n", i, argv[i]);
// 		i++;
// 	}
// }

static void	print_vector(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
	{
		printf("%d: %s\n", i, vector[i]);
		i++;
	}
}

static void	print_envs(t_envs *envs)
{
	while (envs)
	{
		printf("[ (key): %s | (value): %s" \
		"| (internal): %d | (session): %d ]\n", \
		envs->key, envs->value, envs->internal, envs->session);
		envs = envs->next;
	}
}

static void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("TOKEN: %s | TYPE: %d\n", head->content, head->type);
		head = head->next;
	}
}

/* call the debug functions to check the state of the program variables*/
void	call_debug(t_minivault *minivault)
{
	printf("\n---------STRING-------\n");
	if (minivault->line)
		printf("%s\n", minivault->line);
	printf("\n---------VECTOR-------\n");
	if (minivault->input)
		print_vector(minivault->input);
	printf("\n----------LIST--------\n");
	if (minivault->tokens)
		print_tokens(minivault->tokens);
	printf("\n----------TREE--------\n");
	if (minivault)
		print_baobab(minivault);
	printf("\n----------ENV---------\n");
	if (minivault->envs)
		print_envs(minivault->envs);
}
