/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:02:12 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/30 21:31:56 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_minishell	*minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

int	init_minishell(void)
{
	minishell()->envp = NULL;
	minishell()->tree = NULL;
	minishell()->token = NULL;
	minishell()->input = NULL;
	printf("Minishell initialized\n");
	return (0);
}

void	call_debug(int argc, char **argv, char **envs)
{
	print_argv(argc, argv);
	print_envs(envs);
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
