/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:22:42 by jalves-c          #+#    #+#             */
/*   Updated: 2024/04/14 00:59:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_declare_session_envar(t_envs *curr, int out_fd)
{
	ft_putstr_fd("declare -x ", out_fd);
	ft_putstr_fd(curr->key, out_fd);
	ft_putstr_fd("=\"", out_fd);
	ft_putstr_fd(curr->value, out_fd);
	ft_putstr_fd("\"\n", out_fd);
}

static	bool	check_if_exist(t_minivault *minivault, char *key)
{
	char	*val;
	val = get_env(minivault, key);
	if (val)
		return (true);
	return (false);
}

static bool	_valid_key(t_minivault *minivault, char *key, bool *exist, bool *concat)
{
	char	*saved;

	if (!key)
		return (false);
	saved = key;
	if (key[FIRST_ELEM] != '_' && !ft_isalpha(key[FIRST_ELEM]))
		return (false);
	*exist = check_if_exist(minivault, key);
	key++;
	while (*key)
	{
		if (*key == '+' && !(*(key + 1)))
		{
			*key = '\0';
			*concat = true;
			*exist = check_if_exist(minivault, saved);
		}
		else if (*key != '_' && !ft_isalnum(*key))
			return (false);
		key++;
	}
	return (true);
}

static int	add_args_to_env(t_minivault *minivault, t_word *args)
{
	int		_stat;
	bool	exist;
	bool	concat;
	char	*err;
	char	**iter;

	_stat = SUCCESS;
	exist = false;
	concat = false;
	while (args)
	{
		iter = ft_split(args->word, '=');
		if (!iter)
			break ;
		if (_valid_key(minivault, iter[FIRST_ELEM], &exist, &concat))
			add_env_key_val(minivault, iter, exist, concat);
		else
		{
			liberate_vector(iter);
			err = exe_concat(NULL, "minivault: export: `", args->word, "': ",
					"not a valid identifier\n", NULL);
			_stat = FAILURE + (0 * write(STDERR_FILENO, err, ft_strlen(err)));
			free(err);
		}
		args = args->next;
	}
	return (_stat);
}

int	_export(t_minivault *minivault, t_word *args, int out_fd)
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
	set_env(minivault, "?", ft_itoa(_stat), (1 << 1));
	return (_stat);
}
