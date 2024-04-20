/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:24:27 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/20 14:32:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_all(va_list args)
{
	char	*iter;
	char	*temp;
	char	*_string;

	temp = NULL;
	_string = va_arg(args, char *);
	if (!_string)
	{
		return (temp);
	}
	_string = ft_strdup(_string);
	iter = va_arg(args, char *);
	while (iter)
	{
		temp = ft_strjoin(_string, iter);
		free(_string);
		_string = temp;
		if (!_string)
			return (NULL);
		iter = va_arg(args, char *);
	}
	return (_string);
}

static void	_free_or_not_free(bool exist, char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		if (i == 0 && exist)
			free(vec[i]);
		if (i >= 2)
			free(vec[i]);
		i++;
	}
	free(vec);
}

int	handel_invalid_identifier(char **iter, char *word)
{
	int		_stat;
	char	*err;

	liberate_vector(iter);
	err = exe_concat(NULL, "minivault: export: `", word, "': ",
			"not a valid identifier\n", NULL);
	_stat = FAILURE + (0 * write(STDERR_FILENO, err, ft_strlen(err)));
	free(err);
	return (_stat);
}

void	add_env_key_val(t_minivault *minivault, char **iter, \
	bool exist, bool concat)
{
	if (iter[FIRST_ELEM] && iter[SECOND_ELEM])
	{
		if (concat && exist)
		{
			set_env(minivault, iter[FIRST_ELEM], \
					exe_concat(iter[SECOND_ELEM], \
					get_env(minivault, iter[FIRST_ELEM]), \
					iter[SECOND_ELEM], NULL), (1 << 2));
		}
		else
			set_env(minivault, iter[FIRST_ELEM], \
					iter[SECOND_ELEM], (1 << 2));
	}
	else if (iter[FIRST_ELEM] && !exist)
		set_env(minivault, iter[FIRST_ELEM], \
				ft_strdup("\31"), (1 << 2));
	_free_or_not_free(exist, iter);
}

void	clean_exit(t_minivault *minivault, int status)
{
	liberation(minivault);
	exit(status);
}
