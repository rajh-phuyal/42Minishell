/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:15:10 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/09/28 00:03:13 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include <readline/readline.h>
# include <readline/history.h>

char	*readaline(void);
void	init_readline(void);
void	close_readline(void);
void	handle_input(char *input);

#endif