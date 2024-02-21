/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _res_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:54 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:29:55 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd_catcher(t_minivault *minivault)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		minivault->fd_catcher[i] = -1;
		i++;
	}
}

void	empty_fd_catcher(t_minivault *minivault)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		if (minivault->fd_catcher[i] != -1)
			close(minivault->fd_catcher[i]);
		else
			break ;
		i++;
	}
}

void	insert_fd_catcher(t_minivault *minivault, int fd)
{
	int	i;

	i = 0;
	while (i < FOPEN_MAX)
	{
		if (minivault->fd_catcher[i] == -1)
		{
			minivault->fd_catcher[i] = fd;
			break ;
		}
		i++;
	}
}
