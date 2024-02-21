/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:23:16 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 22:08:26 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int in, int out)
{
	if (in != -1 && in != STDIN_FILENO)
		close(in);
	if (out != -1 && out != STDOUT_FILENO)
		close(out);
}
