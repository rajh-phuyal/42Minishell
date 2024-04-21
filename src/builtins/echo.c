/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:49:41 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 21:49:42 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	_existance_flag(char *str)
{
	if (str && str[0] == '-' && str[1] == 'n')
	{
		str += 2;
		while (*str == 'n')
			str++;
		return (*str == '\0');
	}
	return (false);
}

void	_echo(t_minivault *minivault, t_word *args, int out_fd)
{
	bool	is_flag;

	is_flag = false;
	if (args)
	{
		is_flag = _existance_flag(args->word);
		while (args && _existance_flag(args->word))
			args = args->next;
		while (args)
		{
			ft_putstr_fd(args->word, out_fd);
			if (args->next)
				ft_putchar_fd(' ', out_fd);
			args = args->next;
		}
	}
	if (!is_flag)
		ft_putchar_fd('\n', out_fd);
	set_env(minivault, PREVEXITSTAT, ft_itoa(SUCCESS), (1 << 1));
}
