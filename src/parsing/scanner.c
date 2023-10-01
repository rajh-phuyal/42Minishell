/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:59:03 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/30 21:42:25 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char *input)
{
	printf("Lex got: %s\n", input);
	if (*input == 'e')
	{
		free(input);
		exit(0);
	}
}
