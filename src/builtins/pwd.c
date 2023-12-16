/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:25 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/16 23:48:29 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void    _pwd(t_minivault *minivault)
{
    char    buffer[PATH_MAX];

    (void)minivault; // TODO: later use the io fd from executor
    if (!getcwd(buffer, sizeof(buffer)))
        set_env(minivault, "?", ft_itoa(FAILURE), (1 << 1));
    else
        set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
    ft_putendl_fd(buffer, 1);
    return ;
}
