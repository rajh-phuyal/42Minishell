/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:50:20 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 21:50:21 by rphuyal          ###   ########.fr       */
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
