/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:31:05 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/21 17:05:47 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef enum e_sig_state
{
	SIG_STATE_MAIN,
	SIG_STATE_PARENT,
	SIG_STATE_CHILD,
	SIG_STATE_BUILTIN,
	SIG_STATE_HD_CHILD,
	SIG_STATE_IGNORE
}		t_sig_state;

# define SIGNAL_EXIT_HD 2

void	set_signals(t_sig_state sig_state);

#endif