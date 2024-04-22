/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:01:20 by rphuyal           #+#    #+#             */
/*   Updated: 2024/04/21 22:01:22 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '"');
}

bool	is_space(char c)
{
	return (c == '\t' || c == ' ' || c == '\n' || c == '\v');
}
