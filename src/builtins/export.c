/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:59:53 by rajphuyal         #+#    #+#             */
/*   Updated: 2024/01/27 02:36:40 by rajphuyal        ###   ########.fr       */
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

static  bool    _valid_key(char *key)
{
	if (!key)
		return (false);
	if (key[0] != '_' && !ft_isalpha(key[0]))
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

static char	*exe_concat_v2(char *prev, ...)
{
	va_list	args;
	char	*_built;

	va_start(args, prev);
	_built = concat_all(args);
	va_end(args);
	return (_built);
}

static int  add_args_to_env(t_minivault *minivault, t_word *args)
{
    int    _stat;
    char    *err;
    char    **iter;

    _stat = SUCCESS;
    while (args)
    {
        iter = ft_split(args->word, '=');
        if (!iter)
            break ;
        if (_valid_key(iter[FIRST_ELEM]))
        {
            if (iter[FIRST_ELEM] && iter[SECOND_ELEM])
                add_env_node(minivault, iter[FIRST_ELEM], iter[SECOND_ELEM], (1 << 2));
            else if (iter[FIRST_ELEM])
                add_env_node(minivault, iter[FIRST_ELEM], "", (1 << 2));
        }
        else
        {
            err = exe_concat_v2(NULL, "minivault: export: `", args->word, "': ", "not a valid identifier", NULL);
            printf("%s\n", err);
            free(err);
            _stat = FAILURE;
        }
        if (iter)
            free (iter);
        args = args->next;
    }
    return (_stat);
}

//? its not exporting shit, fix it!
void    _export(t_minivault *minivault, t_word *args, int out_fd)
{
    int     _stat;
    t_envs  *curr;
    char    **iter;
    char    **sorted;

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
