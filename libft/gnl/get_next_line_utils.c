/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:54:15 by rphuyal           #+#    #+#             */
/*   Updated: 2022/12/29 19:37:58 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	clear_buffer(char *buffer)
{
	size_t	index;

	index = 0;
	if (!buffer)
		return ;
	while (index < (size_t)BUFFER_SIZE)
		buffer[index++] = '\0';
}

size_t	getuntilnl(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] && str[len] != 10)
		len++;
	return (len + (str[len] == 10));
}

/*
manage buffer helps keep track of the characters if 
the file offset passed a newline.
When a newline is encountered, all the characters after 
the newline are sifted to the start of the buffer.
*/

int	manage_buffer(char *buffer)
{
	char	*start;
	char	*temp;

	start = buffer;
	while (*buffer)
	{
		if (*buffer == 10)
		{
			*buffer = '\0';
			temp = buffer + 1;
			while (*temp)
			{
				*start++ = *temp;
				*temp++ = '\0';
			}
			return (true);
		}
		else
			*buffer++ = '\0';
	}
	return (false);
}

/* 
function create_line joins the last array 
that was pointed by line in get_next_line
and the current buffer until the newline is reached
*/

int	create_line(char **line_ptr, char *buffer, size_t size)
{
	char	*l_alias;
	int		inew;
	int		iold;
	size_t	ibuff;

	inew = 0;
	l_alias = *line_ptr;
	*line_ptr = malloc(sizeof(char) * (size + getuntilnl(l_alias) + 1));
	if (!(*line_ptr))
		return (0);
	if (l_alias)
	{
		iold = 0;
		while (l_alias[iold])
			(*line_ptr)[inew++] = l_alias[iold++];
		free(l_alias);
	}
	ibuff = 0;
	while (ibuff < size)
		(*line_ptr)[inew++] = buffer[ibuff++];
	(*line_ptr)[inew] = '\0';
	return (manage_buffer(buffer));
}
