/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:57:28 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/25 20:44:04 by rajphuyal        ###   ########.fr       */
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

static  t_word  *_skip_options(t_word *args)
{
    while (args)
    {
        if (ft_strncmp(args->word, "-n", ft_strlen(args->word)) != 0)
            return (args);
        _existance(true, false);
        args = args->next;
    }
    return (args);
}

void    _echo(t_minivault *minivault, t_word *args)
{
    (void)minivault;
    _existance(false, false);
    if (args)
    {
        args = _skip_options(args);
        while (args)
        {
            ft_putstr_fd(args->word, STDOUT_FILENO);
            if (args->next)
                ft_putchar_fd(' ', STDOUT_FILENO);
            args = args->next;
        }
        if (!_existance(false, true))
            ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
        ft_putchar_fd('\n', STDOUT_FILENO);
}
