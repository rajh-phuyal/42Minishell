/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:00:41 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:00:43 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// using int instead of bool because va_start
// will have undefined behavior if used with bool
void	error(t_minivault *minivault, t_status status, int prompt, ...)
{
	va_list	args;
	char	*_string;

	va_start(args, prompt);
	_string = concat_all(args);
	va_end(args);
	if (_string)
	{
		if (!prompt)
			ft_putendl_fd(_string, STDERR_FILENO);
		else
		{
			ft_putstr_fd("minibaiters: ", STDERR_FILENO);
			ft_putendl_fd(_string, STDERR_FILENO);
		}
		free(_string);
	}
	if (status != REDIRFAIL)
		cycle_reset(minivault);
	set_env(minivault, "?", ft_itoa(status), (1 << 1));
}
