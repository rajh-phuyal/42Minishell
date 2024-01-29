/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:19:11 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:19:12 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(int *fds)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
		fds[i++] = -1;
}

void	insert_fd(int *fds, int fd)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		if (fds[i] == -1)
		{
			fds[i] = fd;
			break ;
		}
		i++;
	}
}

void	clean_fds(int *fds)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		if (fds[i] != -1)
			close(fds[i]);
		i++;
	}
}
