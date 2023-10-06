/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:02:12 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/06 16:22:24 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* call the debug functions to check the state of the program variables*/
void	call_debug(int argc, char **argv, char **envs, t_minivault *minivault)
{
	print_argv(argc, argv);
	print_envs(envs);
	print_tokens(minivault->tokens);
}

int	main(int argc, char **argv, char **envs)
{
	t_minivault	minivault;

	if (argc != 1)
		return (ft_printf("Minishell doesn't support arguments\n") - 36);
	init_readline();
	init_minivault(&minivault);
	if (false)
		call_debug(argc, argv, envs, &minivault);
	while (true)
		handle_input(&minivault, readaline());
	liberation(&minivault);
	close_readline();
	return (0);
}
