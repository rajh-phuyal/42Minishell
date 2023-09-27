/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:11:36 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/28 00:00:45 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "inputs.h"

// parsing functions
void	lexer(char *input);

// builtin functions

// signal functions

// execution functions

// error functions

// debug functions
void	print_envs(char **envp);
void	print_argv(int argc, char **argv);

#endif