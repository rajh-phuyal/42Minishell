/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:02:12 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/28 00:21:18 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	call_debug(int argc, char **argv, char **envs)
{
	print_argv(argc, argv);
	print_envs(envs);
}

int	init_minishell(void)
{
	printf("Minishell initialized\n");
	return (1);
}

int	main(int argc, char **argv, char **envs)
{
	char	*input;

	if (false)
		call_debug(argc, argv, envs);
	(init_readline() && init_minishell());
	while (true)
	{
		input = readaline();
		handle_input(input);
		free(input);
	}
	close_readline();
	return (0);
}
