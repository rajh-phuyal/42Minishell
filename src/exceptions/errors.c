/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:19:37 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:19:39 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add a panic attack that will kill all the process and exit minishell
// don't know what is the exact use case of panic mode
// if its to exit with a status, call the internal exit function _exit instead
// if just to clean the cycle, call cycle_reset
void	panic_attack(t_minivault *minivault)
{
	cycle_reset(minivault);
	// exit(FAILURE);
}

// using int instead of bool because va_start will have 
//   undefined behavior if used with bool
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
			printf("%s\n", _string);
		else
			printf("minibaiters: %s\n", _string);
		free(_string);
	}
	// if (status != CMDNOTFOUND) //! Fix me!!!
		// cycle_reset(minivault);
	set_env(minivault, "?", ft_itoa(status), (1 << 1));
}
