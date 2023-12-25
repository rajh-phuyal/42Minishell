/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:57:28 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/23 17:42:59 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  bool    _existance(bool exist, bool get)
{
    static	bool	_exist = false;

    if (get)
        return (_exist);
    _exist = exist;
    return (exist);
}

static  char    **_skip_options(char **args)
{
    while (args && *args)
    {
        if (ft_strncmp(*args, "-n", ft_strlen(*args)) != 0)
            return (args);
        _existance(true, false);
        args++;
    }
    return (args);
}

void    _echo(t_minivault *minivault, char **args)
{
    (void)minivault;
    _existance(false, false);
    if (args && *args)
    {
        args = _skip_options(args);
        while (args && *args)
        {
            ft_putstr_fd(*args, 1);
            ft_putchar_fd(' ', 1);
            args++;
        }
        if (!_existance(false, true))
            ft_putchar_fd('\n', 1);
    }
    else
        ft_putchar_fd('\n', 1);
}
