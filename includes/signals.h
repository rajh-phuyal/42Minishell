/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:20:40 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:32:24 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "minishell.h"
# include "inputs.h"
# include "executor.h"
# include "signals.h"

typedef enum e_sig_state
{
	SIG_STATE_MAIN,
	SIG_STATE_PARENT,
	SIG_STATE_CHILD,
	SIG_STATE_CHILD_BUILTIN,
	SIG_STATE_HD_CHILD,
	SIG_STATE_IGNORE
}				t_sig_state;

# define SIGNAL_EXIT_HD 2

void	set_signals(t_sig_state	sig_state);

#endif