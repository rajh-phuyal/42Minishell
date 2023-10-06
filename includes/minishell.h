/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:11:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/10/04 19:34:32 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// custom
# include "../libft/libft.h"
# include "inputs.h"
# include "executor.h"
# include "signals.h"

// system
# include <stdbool.h>

// the minieverything
typedef struct s_minivault
{
	char		**envp;
	char		*input;
	t_baobab	*baobab;
	t_token		*tokens;
}	t_minivault;

t_minivault	*minishell(void);

// minishell
int			init_minivault(t_minivault *minivault);

// parsing gate
void		lexer(t_minivault *minivault, char *input);

// debug functions
void		print_envs(char **envp);
void		print_argv(int argc, char **argv);

// the liberator
void    	liberation(t_minivault *minivault);

#endif