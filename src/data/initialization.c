/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:35:41 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/30 21:42:04 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(void)
{
	minishell()->envp = NULL;
	minishell()->tree = NULL;
	minishell()->token = NULL;
	minishell()->input = NULL;
	printf("Minishell initialized\n");
	return (0);
}
