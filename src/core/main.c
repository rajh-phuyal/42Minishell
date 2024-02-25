/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:54 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:22:55 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

int	main(int argc, char **argv, char **envs)
{
	t_minivault	minivault;

	(void)argc;
	(void)argv;
	set_signals(SIG_STATE_MAIN);
	init_minivault(&minivault, envs);
	while (true)
		handle_input(&minivault, readaline());
	return (0);
}

// Dear programmer:
// When I wrote this code, only god and
// I knew how it worked.
// Now, only god knows it!
//
// Therefore, if you are trying to optimize it, and it fails (most surely),
// please increase this counter as a warning for the next person:
//
// total_hours_wasted_here = 258