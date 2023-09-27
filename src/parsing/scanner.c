/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:59:03 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/28 00:02:56 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer(char *input)
{
	printf("Lex got: %s\n", input);
	if (*input == 'e')
	{
		free(input);
		exit(0);
	}
}
