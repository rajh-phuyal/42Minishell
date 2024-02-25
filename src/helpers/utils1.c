/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:48:09 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 18:48:10 by jalves-c         ###   ########.fr       */
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
