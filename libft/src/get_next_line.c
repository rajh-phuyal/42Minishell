/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:33:55 by jalves-c          #+#    #+#             */
/*   Updated: 2023/05/04 19:02:06 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		index;

	index = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		while (buffer[index])
			buffer[index++] = 0;
		return (0);
	}
	line = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE))
	{
		line = strjoin(line, buffer);
		if (ft_manage_buffer(buffer))
			break ;
	}
	return (line);
}
