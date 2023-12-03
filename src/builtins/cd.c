/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:55:58 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/03 00:12:17 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    _cd(t_minivault *minivault,  char *path)
{
    static char	*oldpath = NULL;

    // relative paths are ..
    // absolute paths are /Users/rajphuyal/Desktop/42/minishell
    // validate path
	// if path is NULL, go to HOME
	// if path is -, go to OLDPWD
	// if path is ~, go to HOME
	// if path is ., do nothing
	// if path is .., go to parent directory
	// if path is /, go to root directory
	// if path is anything else, go to that directory
	// if a path is incorrect, print error message (bash: cd: blah: No such file or directory)
	// if a path is a file, print error message (bash: cd: blah: Not a directory)
	// if a path is a directory, go to that directory

    // change directory using the path

    // update PWD
}