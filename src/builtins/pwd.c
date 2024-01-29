/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:20:11 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:20:12 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pwd(t_minivault *minivault, int out_fd)
{
	char	buffer[PATH_MAX];

	(void)minivault;
	if (!getcwd(buffer, sizeof(buffer)))
		set_env(minivault, PREVEXITSTAT, ft_itoa(FAILURE), (1 << 1));
	else
		set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
	ft_putendl_fd(buffer, out_fd);
	return ;
}
