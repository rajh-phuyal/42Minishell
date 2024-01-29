/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:20:14 by jalves-c          #+#    #+#             */
/*   Updated: 2024/01/29 18:20:15 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_free_or_not_free(char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		if (i >= 2)
			free(vec[i]);
		i++;
	}
}

static void	_declare_session_envar(t_envs *curr, int out_fd)
{
	ft_putstr_fd("declare -x ", out_fd);
	ft_putstr_fd(curr->key, out_fd);
	ft_putstr_fd("=\"", out_fd);
	ft_putstr_fd(curr->value, out_fd);
	ft_putstr_fd("\"\n", out_fd);
}

static bool	_valid_key(char *key)
{
	if (!key)
		return (false);
	if (key[FIRST_ELEM] != '_' && !ft_isalpha(key[FIRST_ELEM]))
		return (false);
	key++;
	while (*key)
	{
		if (*key != '_' && !ft_isalnum(*key))
			return (false);
		key++;
	}
	return (true);
}

static int	add_args_to_env(t_minivault *minivault, t_word *args)
{
	int		_stat;
	char	*err;
	char	**iter;

	_stat = SUCCESS;
	while (args)
	{
		iter = ft_split(args->word, '=');
		if (!iter)
			break ;
		if (_valid_key(iter[FIRST_ELEM]))
		{
			if (iter[FIRST_ELEM] && iter[SECOND_ELEM])
				set_env(minivault, iter[FIRST_ELEM], \
				iter[SECOND_ELEM], (1 << 2));
			else if (iter[FIRST_ELEM])
				set_env(minivault, \
				iter[FIRST_ELEM], "", (1 << 2));
			_free_or_not_free(iter);
			free(iter);
		}
		else
		{
			liberate_vector(iter);
			err = exe_concat(NULL, "minivault: export: `", \
			args->word, "': ", "not a valid identifier", NULL);
			printf("%s\n", err);
			free(err);
			_stat = FAILURE;
		}
		args = args->next;
	}
	return (_stat);
}

void	_export(t_minivault *minivault, t_word *args, int out_fd)
{
	int		_stat;
	t_envs	*curr;
	char	**iter;
	char	**sorted;

	_stat = SUCCESS;
	if (args)
		_stat = add_args_to_env(minivault, args);
	else
	{
		sorted = envsort(minivault->envs);
		iter = sorted;
		while (iter && *iter)
		{
			curr = get_env_node(minivault, *iter);
			if (curr && (curr->session) && !(curr->internal))
				_declare_session_envar(curr, out_fd);
			iter++;
		}
		if (sorted)
			free(sorted);
	}
	set_env(minivault, PREVEXITSTAT, ft_itoa(_stat), (1 << 1));
}
